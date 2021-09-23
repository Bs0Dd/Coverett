#include "../coverett-private.h"
#include "../coverett.h"


RESULT universalSound(DEVICE* dev, char* name, char* method){
	if (strcmp(dev->devType, "oc2:sound_card") != 0) return (RESULT){RESULT_ERROR, 0, NULL, NULL, "Incorrect device type"};
	char* strvals[] = {name};
	int packord[] = {1};
	return universalInvoker(dev, method, NULL, strvals, 1, packord);
}



RESULT playSound(DEVICE* device, char* name){
	return universalSound(device, name, "playSound");
}

LIST findSound(DEVICE* device, char* string){
	RESULT res = universalSound(device, string, "findSound");
	if (res.type == RESULT_ERROR){
		return (LIST){LIST_ERROR, NULL, res.errString};
	}
	return (LIST){LIST_SOUNDS, res.retList, NULL};
}

char** getSoundsName(LIST sounds, int* totalsounds){
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
