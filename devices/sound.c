#include "../coverett-private.h"
#include "../coverett.h"


result_t universalSound(device_t* dev, char* name, char* method){
	if (strcmp(dev->devType, "oc2:sound_card") != 0) return (result_t){RESULT_ERROR, 0, NULL, NULL, "Incorrect device type"};
	char* strvals[] = {name};
	int packord[] = {1};
	return universalInvoker(dev, method, NULL, strvals, 1, packord);
}



result_t playSound(device_t* device, char* name){
	return universalSound(device, name, "playSound");
}

list_t findSound(device_t* device, char* string){
	result_t res = universalSound(device, string, "findSound");
	if (res.type == RESULT_ERROR){
		return (list_t){LIST_ERROR, NULL, res.errString};
	}
	return (list_t){LIST_SOUNDS, res.retList, NULL};
}

char** getSoundsName(list_t sounds, int* totalsounds){
	if (sounds.type != LIST_SOUNDS) return NULL;
	char** nameslist = (char**)calloc(cJSON_GetArraySize(sounds.body), sizeof(char*));
	*totalsounds = 0;
	cJSON* name = NULL;
	cJSON_ArrayForEach(name, sounds.body){
		nameslist[*totalsounds] = name->valuestring;
		(*totalsounds)++;
	}
	return nameslist;
}
