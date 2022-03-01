#include "coverett-private.h"

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
	if (list.type != CO_DEVICES) return dev;
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
