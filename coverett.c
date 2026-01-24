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
	device_t dev = CO_NULL_DEVICE;
	if (id == NULL) return dev;
	int totalnames;
	char** names = getDevNamesById(list, id, &totalnames);
	if (names == NULL) return dev;
	for (int i = 0; i < totalnames; i++){
		if (!strcmp(name, names[i])){
			dev = (device_t){1, name, id, bus};
			return dev;
		}
	}
	return CO_NULL_DEVICE;
}

list_t getMethods(device_t* device){
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

method_t* parseMethods(list_t list, int* meths){
	if (list.type != CO_METHODS) {
		return NULL;
	}
	*meths = cJSON_GetArraySize(list.body);
	if (*meths < 1) {
		return NULL;
	}
	method_t* ret = (method_t*)calloc(*meths, sizeof(method_t));
	cJSON* val = NULL;
	cJSON* method = NULL;
	int i = 0;
	cJSON_ArrayForEach(method, list.body){
		val = cJSON_GetObjectItemCaseSensitive(method, "name");
		ret[i].name = val == NULL ? NULL : strdup(val->valuestring);
		val = cJSON_GetObjectItemCaseSensitive(method, "returnType");
		ret[i].returnType = val == NULL ? NULL : strdup(val->valuestring);
		val = cJSON_GetObjectItemCaseSensitive(method, "description");
		ret[i].description = val == NULL ? NULL : strdup(val->valuestring);
		val = cJSON_GetObjectItemCaseSensitive(method, "returnValueDescription");
		ret[i].returnValueDescription = val == NULL ? NULL : strdup(val->valuestring);
		cJSON* parms = cJSON_GetObjectItemCaseSensitive(method, "parameters");
		if (parms != NULL && cJSON_GetArraySize(parms) > 0) {
			ret[i].paramNum = cJSON_GetArraySize(parms);
			param_t* par = (param_t*)calloc(cJSON_GetArraySize(parms), sizeof(param_t));
			cJSON* parm = NULL;
			int j = 0;
			cJSON_ArrayForEach(parm, parms){
				val = cJSON_GetObjectItemCaseSensitive(parm, "name");
				par[j].name = val == NULL ? NULL : strdup(val->valuestring);
				val = cJSON_GetObjectItemCaseSensitive(parm, "type");
				par[j].type = val == NULL ? NULL : strdup(val->valuestring);
				val = cJSON_GetObjectItemCaseSensitive(parm, "description");
				par[j].description = val == NULL ? NULL : strdup(val->valuestring);
				j++;
			}
			ret[i].parameters = par;
		} else{
			ret[i].parameters = NULL;
		}
		i++;
	}
	return ret;
}

void deleteParsedMethods(method_t* methods, int meths){
	if (methods == NULL) {
		return;
	}
	for (int i = 0; i < meths; i++){
		if (methods[i].name != NULL) free(methods[i].name);
		if (methods[i].returnType != NULL) free(methods[i].returnType);
		if (methods[i].description != NULL) free(methods[i].description);
		if (methods[i].returnValueDescription != NULL) free(methods[i].returnValueDescription);
		for (int j = 0; j < methods[i].paramNum; j++){
			if (methods[i].parameters[j].name != NULL) free(methods[i].parameters[j].name);
			if (methods[i].parameters[j].type != NULL) free(methods[i].parameters[j].type);
			if (methods[i].parameters[j].description != NULL) free(methods[i].parameters[j].description);
		}
		if (methods[i].parameters != NULL) free(methods[i].parameters);
	}
	free(methods);
    methods = NULL;
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
			for (int k = 0; k < len; k++){
				cJSON_AddItemToArray(array, cJSON_CreateNumber((double)(strvals[pointstr][k]))); //ACHTUNG!!! Looks like some values changing to 0 by unknown reason!
			}
			cJSON_AddItemToArray(params, array);
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
		int retn = ans->valuedouble;
		cJSON_Delete(ans);
		return (result_t){CO_NUMBER, retn, NULL, NULL, NULL};
	}
	else if (cJSON_IsArray(ans)){
		if (cJSON_IsNumber(cJSON_GetArrayItem(ans, 0))){
			int siz = cJSON_GetArraySize(ans);
			char* bytes = (char*)malloc(siz);
			for (int i = 0; i < siz; i++){
				bytes[i] = cJSON_GetArrayItem(ans, i)->valuedouble;
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

