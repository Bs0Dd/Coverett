#include "coverett-private.h"
#include "coverett.h"

void writeData(bus_t bus, char* body){
	fputc(0, bus); // Start delimiter
	fputs(body, bus);
	fputc(0, bus); // End delimiter
}

char* readData(bus_t bus){
	if (fgetc(bus) == 0){
		int len = 0;
		int capacity = 1024;
		char* result = (char*)malloc(capacity);
		char c = fgetc(bus);

		while (c != '\0'){
			result[len++] = c;

			if (len >= capacity){
				capacity += 1024;
				result = (char*)realloc(result, capacity); 
			}
			c = fgetc(bus);         
		}

		result[len] = c;
		return result;
	}
	return "\0";
}

cJSON* request(bus_t bus, char* body, char* exptype, int* status){
	writeData(bus, body);
	char* rawans = readData(bus);
	cJSON* ansjson = cJSON_Parse(rawans);
	free(rawans);
	char* type = cJSON_GetObjectItemCaseSensitive(ansjson, "type")->valuestring;
	if (strcmp(type, exptype) == 0){
		*status = 0;
	}
	else if (strcmp(type, "error") == 0){
		*status = -1;
	}
	else{
		*status = -2;
	}
	return cJSON_GetObjectItemCaseSensitive(ansjson, "data");
}

device_t proxyDevByList(bus_t bus, list_t list, char* id){
	device_t dev = {0, NULL, NULL, NULL};
	if (list.type != LIST_LIST) return dev;
	int totalnames;
	char** names = getDevNamesById(list, id, &totalnames);
	cJSON_Delete(list.body);
	if (names == NULL) return dev;
	for (int i = 0; i < totalnames; i++){
		if (strstr(names[i], "oc2:") != NULL || strcmp(names[i], "robot") == 0){
			dev.exists = 1;
			dev.devType = names[i];
			dev.devId = id;
			dev.busPtr = bus;
			return dev;
		}
	}
	return dev;
}

int existsStatus(device_t* dev){
	list_t list = getList(dev->busPtr);
	cJSON* device = NULL;
	cJSON_ArrayForEach(device, list.body){
		char* devid = cJSON_GetObjectItemCaseSensitive(device, "deviceId")->valuestring;
		if (strcmp(dev->devId, devid) == 0){
			dev->exists = 1;
			cJSON_Delete(list.body);
			return 1;
		}
	}
	cJSON_Delete(list.body);
	dev->exists = 0;
	return 0;
}

result_t universalInvoker(device_t* dev, char* methodname, int* numvals, char** strvals, int nofpar, int* packord){
	if (!dev->exists || !existsStatus(dev)) return (result_t){RESULT_ERROR, 0, NULL, NULL, "Device is no longer available"};
	cJSON* reqbody = cJSON_CreateObject();
	cJSON_AddStringToObject(reqbody, "type", "invoke");
	cJSON* data = cJSON_CreateObject();
	cJSON_AddItemToObject(reqbody, "data", data);
	cJSON_AddStringToObject(data, "deviceId", dev->devId);
	cJSON_AddStringToObject(data, "name", methodname);
	cJSON* params = cJSON_AddArrayToObject(data, "parameters");
	int pointnum = 0;
	int pointstr = 0;
	for (int i = 0; i < nofpar; i++){
		if (packord[i] == 0){ // Add integer to parameters array
			cJSON_AddItemToArray(params, cJSON_CreateNumber(numvals[pointnum++]));
		}
		else if (packord[i] == 1){ // Add string to parameters array
			cJSON_AddItemToArray(params, cJSON_CreateString(strvals[pointstr++]));
		}
		else if (packord[i] == 2){ // Add bytes to parameters array, next value in packord - bytes length
			int len = packord[++i];
			cJSON* array = cJSON_CreateArray();
			cJSON_AddItemToArray(params, array);
			for (int k = 0; k < len; k++){
				cJSON_AddItemToArray(array, cJSON_CreateNumber(strvals[pointstr][k]));
			}
			pointstr++;
		}
	}
	int resstat;
	cJSON* ans = request(dev->busPtr, cJSON_Print(reqbody), "result", &resstat);
	cJSON_Delete(reqbody);
	if (resstat == -1){
		char* errstr = strdup(ans->valuestring);
		cJSON_Delete(ans);
		return (result_t){RESULT_ERROR, 0, NULL, NULL, errstr};
	}
	else if (resstat == -2){
		cJSON_Delete(ans);
		return (result_t){RESULT_ERROR, 0, NULL, NULL, "Incorrect answer"};
	}
	if (resstat == 0 && ans == NULL){
		return (result_t){RESULT_VOID, 0, NULL, NULL, NULL};
	}
	else if (cJSON_IsNumber(ans)){
		int retn = ans->valueint;
		cJSON_Delete(ans);
		return (result_t){RESULT_NUMBER, retn, NULL, NULL, NULL};
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
			return (result_t){RESULT_BYTES, siz, bytes, NULL, NULL};
		}
		else{
			return (result_t){RESULT_LIST, 0, NULL, ans, NULL};	
		}
	}
	else if (cJSON_IsString(ans)){
		char* rets = strdup(ans->valuestring);
		cJSON_Delete(ans);
		return (result_t){RESULT_STRING, 0, rets, NULL, NULL};
	}
	else if (cJSON_IsBool(ans)){
		int retb = cJSON_IsTrue(ans);
		cJSON_Delete(ans);
		return (result_t){RESULT_BOOLEAN, retb, NULL, NULL, NULL};
	}
	else if (cJSON_IsObject(ans)){
		return (result_t){RESULT_LIST, 0, NULL, ans, NULL};
	}
}
