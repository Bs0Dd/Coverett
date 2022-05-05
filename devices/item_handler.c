#include "../coverett.h"


const result_t IHINC = {CO_ERROR, 0, NULL, NULL, "Incorrect device type"};

int isItHand(device_t* dev){
	return strcmp(dev->devType, "oc2:computer") == 0 || strcmp(dev->devType, "oc2:disk_drive") == 0;
}



result_t getHandlerSlotCount(device_t* device){
	if (!isItHand(device)) return IHINC;
	return uniInvoke(device, "getSlotCount", NULL, NULL, 0, NULL);
}

result_t getHandlerSlotLimit(device_t* device, int slot){ // a slot? idk, in methods list this is named as "arg1", so it maybe not a slot
	if (!isItHand(device)) return IHINC;
	double numparams[] = {slot};
	cotypes_t packord[] = {CO_NUMBER};
	return uniInvoke(device, "getSlotLimit", numparams, NULL, 1, packord);
}

stackinfo_t getHandlerStackInSlot(device_t* device, int slot){ // a slot? idk, in methods list this is named as "arg1", so it maybe not a slot
	if (!isItHand(device)) return (stackinfo_t){CO_ERROR, NULL, 0, IHINC.errString};
	double numparams[] = {slot};
	cotypes_t packord[] = {CO_NUMBER};
	result_t res = uniInvoke(device, "getStackInSlot", numparams, NULL, 1, packord);
	if (res.type == CO_ERROR){
		return (stackinfo_t){CO_ERROR, NULL, 0, res.errString};
	}
	else if (res.type == CO_VOID){
		return (stackinfo_t){CO_EMPTY, NULL, 0, NULL};
	}
	char* id = strdup(cJSON_GetObjectItemCaseSensitive(res.retList, "id")->valuestring);
	int count = cJSON_GetObjectItemCaseSensitive(res.retList, "Count")->valueint;
	cJSON_Delete(res.retList);
	return (stackinfo_t){CO_OK, id, count, NULL};
}
