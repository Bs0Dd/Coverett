#include "coverett-private.h"


bus_t openBus(char* path){
	bus_t newbus = fopen(path, "r+");
	if (newbus != NULL){
		char* cmd = (char*) malloc (19+strlen(path));
        sprintf(cmd, "stty -F %s raw -echo", path);
		system(cmd);
		free(cmd);
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
		return (list_t){LIST_LIST, ans};
	}
	cJSON_Delete(ans);
	return (list_t){LIST_ERROR, NULL, "Failed to get list"};
}

void deleteList(list_t* list){
	if (list->type == LIST_ERROR) return;
	cJSON_Delete(list->body);
	*list = (list_t){LIST_DELETED, NULL};
}

char** getDevsId(list_t list, int* totaldevices){
	if (list.type != LIST_LIST) return NULL;
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
	if (list.type != LIST_LIST) return NULL;
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
	if (list.type != LIST_LIST) return NULL;
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

list_t getMethods(device_t* device){ //TODO: Methods parsing
	if (!existsStatus(device)) return (list_t){LIST_ERROR, NULL};
	char reqbody[65];
	sprintf(reqbody, "{\"type\":\"methods\",\"data\":\"%s\"}", device->devId);
	
	int res;
	cJSON* ans = request(device->busPtr, reqbody, "methods", &res);
	if (res == 0){
		return (list_t){LIST_METHODS, ans};
	}
	return (list_t){LIST_ERROR, NULL};
}
