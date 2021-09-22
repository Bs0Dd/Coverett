#include "coverett-private.h"


BUS openBus(char* path){
	BUS newbus = fopen(path, "r+");
	if (newbus != NULL){
		char* cmd = (char*) malloc (19+strlen(path));
		strcpy(cmd, "stty -F ");
		strcat(cmd, path);
		strcat(cmd, " raw -echo");
		system(cmd);
		free(cmd);
	}
	return newbus;
}

int closeBus(BUS bus){
	return fclose(bus);
}

LIST getList(BUS bus){
	int res;
	cJSON* ans = request(bus, "{\"type\":\"list\"}", "list", &res);
	if (res == 0){
		return (LIST){LIST_LIST, ans};
	}
	cJSON_Delete(ans);
	return (LIST){LIST_ERROR, NULL, "Failed to get list"};
}

void deleteList(LIST* list){
	if (list->type == LIST_ERROR) return;
	cJSON_Delete(list->body);
	*list = (LIST){LIST_DELETED, NULL};
}

char** getDevsId(LIST list, int* totaldevices){
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

char** getDevNamesByPos(LIST list, int position, int* totalnames){
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

char** getDevNamesById(LIST list, char* id, int* totalnames){
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

char* getDevIdByName(LIST list, char* name){
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

DEVICE proxyDev(BUS bus, char* id){
	LIST list = getList(bus);
	return proxyDevByList(bus, list, id);
}

DEVICE findDev(BUS bus, char* name){
	LIST list = getList(bus);
	char* id = getDevIdByName(list, name);
	if (id == NULL){
		DEVICE dev = {0, NULL, NULL, NULL};
		return dev;
	}
	if (strstr(name, "oc2:") != NULL || strcmp(name, "robot") == 0){
		DEVICE dev = {1, name, id, bus};
		return dev;
	}
	return proxyDevByList(bus, list, id);
}

LIST getMethods(DEVICE* device){ //TODO: Methods parsing
	if (!existsStatus(device)) return (LIST){LIST_ERROR, NULL};
	char reqbody[65];
	sprintf(reqbody, "{\"type\":\"methods\",\"data\":\"%s\"}", device->devId);
	
	int res;
	cJSON* ans = request(device->busPtr, reqbody, "methods", &res);
	if (res == 0){
		return (LIST){LIST_METHODS, ans};
	}
	return (LIST){LIST_ERROR, NULL};
}
