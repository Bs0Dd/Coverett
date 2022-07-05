#include "coverett.h"
#include "coverett-private.h"

bus_t openBus(char* path){
	bus_t newbus = fopen(path, "r+");
	if (newbus != NULL){
		int fd = fileno(newbus);
		struct termios tcattr;
		tcgetattr(fd, &tcattr);
		cfmakeraw(&tcattr);
		tcsetattr(fd, TCSANOW, &tcattr);
	}
	return newbus;
}

int closeBus(bus_t bus){
	return fclose(bus);
}

list_t getList(bus_t bus){
	int res;
	cJSON* ans = request(bus, "{\"type\":\"list\"}", "list", &res);
	if (res == 0){
		return (list_t){CO_DEVICES, ans};
	}
	cJSON_Delete(ans);
	return (list_t){CO_ERROR, NULL, "Failed to get list"};
}

void deleteList(list_t* list){
	if (list->type == CO_ERROR) return;
	cJSON_Delete(list->body);
	*list = (list_t){CO_DELETED, NULL};
}

char** getDevsId(list_t list, int* totaldevices){
	if (list.type != CO_DEVICES) return NULL;
	char** idlist = (char**)calloc(cJSON_GetArraySize(list.body), sizeof(char*));
	*totaldevices = 0;
	cJSON* device = NULL;
	cJSON_ArrayForEach(device, list.body){
		idlist[*totaldevices] = cJSON_GetObjectItemCaseSensitive(device, "deviceId")->valuestring;
		(*totaldevices)++;
	}
	return idlist;
}

char** getDevNamesByPos(list_t list, int position, int* totalnames){
	if (list.type != CO_DEVICES) return NULL;
	if (position+1 > cJSON_GetArraySize(list.body)) return NULL;
	cJSON* names = cJSON_GetObjectItemCaseSensitive(cJSON_GetArrayItem(list.body, position), "typeNames");
	char** nameslist = (char**)calloc(cJSON_GetArraySize(names), sizeof(char*));
	*totalnames = 0;
	cJSON* name = NULL;
	cJSON_ArrayForEach(name, names){
		nameslist[*totalnames] = strdup(name->valuestring);
		(*totalnames)++;
	}
	return nameslist;
}

char** getDevNamesById(list_t list, char* id, int* totalnames){
	if (list.type != CO_DEVICES) return NULL;
	int counter = 0;
	cJSON* device = NULL;
	cJSON_ArrayForEach(device, list.body){
		char* devid = cJSON_GetObjectItemCaseSensitive(device, "deviceId")->valuestring;
		if (strcmp(id, devid) == 0){
			return getDevNamesByPos(list, counter, totalnames);
		}
		counter++;
	}
	return NULL;
}

char* getDevIdByName(list_t list, char* name){
	if (list.type != CO_DEVICES) return NULL;
	cJSON* device = NULL;
	cJSON_ArrayForEach(device, list.body){
		cJSON* names = cJSON_GetObjectItemCaseSensitive(device, "typeNames");
		cJSON* curname = NULL;
		cJSON_ArrayForEach(curname, names){
			if (strcmp(curname->valuestring, name) == 0){
				return strdup(cJSON_GetObjectItemCaseSensitive(device, "deviceId")->valuestring);
			}
		}
	}
	return NULL;
}

device_t proxyDev(bus_t bus, char* id){
	list_t list = getList(bus);
	return proxyDevByList(bus, list, id);
}

device_t findDev(bus_t bus, char* name){
	list_t list = getList(bus);
	char* id = getDevIdByName(list, name);
	if (id == NULL){
		device_t dev = {0, NULL, NULL, NULL};
		return dev;
	}
	if (strstr(name, "oc2:") != NULL || strcmp(name, "robot") == 0){
		device_t dev = {1, name, id, bus};
		return dev;
	}
	return proxyDevByList(bus, list, id);
}

list_t getMethods(device_t* device){ //TODO: Methods parsing!!!
	if (!existsStatus(device)) return (list_t){CO_ERROR, NULL};
	char reqbody[65];
	sprintf(reqbody, "{\"type\":\"methods\",\"data\":\"%s\"}", device->devId);
	
	int res;
	cJSON* ans = request(device->busPtr, reqbody, "methods", &res);
	if (res == 0){
		return (list_t){CO_METHODS, ans};
	}
	return (list_t){CO_ERROR, NULL};
}

result_t uniInvoke(device_t* dev, char* method, double* numvals, char** strvals, int total, cotypes_t* order){
	if (!dev->exists || !existsStatus(dev)) return (result_t){CO_ERROR, 0, NULL, NULL, "Device is no longer available"};
	cJSON* reqbody = cJSON_CreateObject();
	cJSON_AddStringToObject(reqbody, "type", "invoke");
	cJSON* data = cJSON_CreateObject();
	cJSON_AddItemToObject(reqbody, "data", data);
	cJSON_AddStringToObject(data, "deviceId", dev->devId);
	cJSON_AddStringToObject(data, "name", method);
	cJSON* params = cJSON_AddArrayToObject(data, "parameters");
	int pointnum = 0;
	int pointstr = 0;
	for (int i = 0; i < total; i++){
		if (order[i] == CO_NUMBER){ // Add integer to parameters array
			cJSON_AddItemToArray(params, cJSON_CreateNumber(numvals[pointnum++]));
		}
		else if (order[i] == CO_STRING){ // Add string to parameters array
			cJSON_AddItemToArray(params, cJSON_CreateString(strvals[pointstr++]));
		}
		else if (order[i] == CO_BYTES){ // Add bytes to parameters array, next value in numvals - bytes length
			int len = numvals[pointnum++];
			cJSON* array = cJSON_CreateArray();
			cJSON_AddItemToArray(params, array);
			for (int k = 0; k < len; k++){
				cJSON_AddItemToArray(array, cJSON_CreateNumber(strvals[pointstr][k]));
			}
			pointstr++;
		}
	}
	int resstat;
	cJSON* ans = request(dev->busPtr, cJSON_PrintUnformatted(reqbody), "result", &resstat);
	cJSON_Delete(reqbody);
	if (resstat == -1){
		char* errstr = strdup(ans->valuestring);
		cJSON_Delete(ans);
		return (result_t){CO_ERROR, 0, NULL, NULL, errstr};
	}
	else if (resstat == -2){
		cJSON_Delete(ans);
		return (result_t){CO_ERROR, 0, NULL, NULL, "Incorrect answer"};
	}
	if (resstat == 0 && ans == NULL){
		return (result_t){CO_VOID, 0, NULL, NULL, NULL};
	}
	else if (cJSON_IsNumber(ans)){
		int retn = ans->valueint;
		cJSON_Delete(ans);
		return (result_t){CO_NUMBER, retn, NULL, NULL, NULL};
	}
	else if (cJSON_IsArray(ans)){
		if (cJSON_IsNumber(cJSON_GetArrayItem(ans, 0))){
			cJSON* byte = NULL;
			int i = 0;
			int siz = cJSON_GetArraySize(ans);
			char* bytes = (char*)malloc(siz);
			for (int i = 0; i < siz; i++){
				bytes[i] = cJSON_GetArrayItem(ans, i)->valueint;
			}
			cJSON_Delete(ans);
			return (result_t){CO_BYTES, siz, bytes, NULL, NULL};
		}
		else{
			return (result_t){CO_LIST, 0, NULL, ans, NULL};	
		}
	}
	else if (cJSON_IsString(ans)){
		char* rets = strdup(ans->valuestring);
		cJSON_Delete(ans);
		return (result_t){CO_STRING, 0, rets, NULL, NULL};
	}
	else if (cJSON_IsBool(ans)){
		int retb = cJSON_IsTrue(ans);
		cJSON_Delete(ans);
		return (result_t){CO_BOOLEAN, retb, NULL, NULL, NULL};
	}
	else if (cJSON_IsObject(ans)){
		return (result_t){CO_LIST, 0, NULL, ans, NULL};
	}
}
