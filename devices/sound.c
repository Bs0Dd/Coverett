#include "../coverett.h"
#include <math.h>


int isSound(device_t* dev){
	return strcmp(dev->devType, "sound") == 0; // Another LOC? Change back to "oc2r:sound_card" later
}



result_t playSound(device_t* device, char* name, double volume, double pitch){
	if (!isSound(device)) return (result_t){CO_ERROR, 0, NULL, NULL, "Incorrect device type"};
	char* strvals[] = {name};
	volume = isnan(volume) ? 1 : volume;
	pitch = isnan(pitch) ? 1 : pitch;
	double numvals[] = {volume, pitch};
	cotypes_t packord[] = {CO_STRING, CO_NUMBER, CO_NUMBER};
	return uniInvoke(device, "playSound", numvals, strvals, 3, packord);
}

list_t findSound(device_t* device, char* string){
	if (!isSound(device)) return (list_t){CO_ERROR, NULL};
	char* strvals[] = {string};
	cotypes_t packord[] = {CO_STRING};
	result_t res = uniInvoke(device, "findSound", NULL, strvals, 1, packord);
	if (res.type == CO_ERROR){
		return (list_t){CO_ERROR, NULL, res.errString};
	}
	return (list_t){CO_SOUNDS, res.retList, NULL};
}

char** getSoundsName(list_t sounds, int* totalsounds){
	if (sounds.type != CO_SOUNDS) return NULL;
	char** nameslist = (char**)calloc(cJSON_GetArraySize(sounds.body), sizeof(char*));
	*totalsounds = 0;
	cJSON* name = NULL;
	cJSON_ArrayForEach(name, sounds.body){
		nameslist[*totalsounds] = name->valuestring;
		(*totalsounds)++;
	}
	return nameslist;
}
