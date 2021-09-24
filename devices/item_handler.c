#include "../coverett-private.h"
#include "../coverett.h"


const result_t IHINC = {RESULT_ERROR, 0, NULL, NULL, "Incorrect device type"};

int isItHand(device_t* dev){
	if (strcmp(dev->devType, "oc2:computer") != 0 || strcmp(dev->devType, "oc2:disk_drive") != 0){
		return 0;
	}
	return 1;
}



result_t getHandlerSlotCount(device_t* device){
	if (!isItHand(device)) return IHINC;
	return universalInvoker(device, "getSlotCount", NULL, NULL, 0, NULL);
}

result_t getHandlerSlotLimit(device_t* device, int slot){ // a slot? idk, in methods list this is named as "arg1", so it maybe not a slot
	if (!isItHand(device)) return IHINC;
	int numparams[] = {slot};
	int packord[] = {0};
	return universalInvoker(device, "getSlotLimit", numparams, NULL, 1, packord);
}

stackinfo_t getHandlerStackInSlot(device_t* device, int slot){ // a slot? idk, in methods list this is named as "arg1", so it maybe not a slot
	if (!isItHand(device)) return (stackinfo_t){STACKINFO_ERROR, NULL, 0, IHINC.errString};
	int numparams[] = {slot};
	int packord[] = {0};
	result_t res = universalInvoker(device, "getStackInSlot", numparams, NULL, 1, packord);
	if (res.type == RESULT_ERROR){
		return (stackinfo_t){STACKINFO_ERROR, NULL, 0, res.errString};
	}
	else if (res.type == RESULT_VOID){
		return (stackinfo_t){STACKINFO_EMPTY, NULL, 0, NULL};
	}
	char* id = strdup(cJSON_GetObjectItemCaseSensitive(res.retList, "id")->valuestring);
	int count = cJSON_GetObjectItemCaseSensitive(res.retList, "Count")->valueint;
	cJSON_Delete(res.retList);
	return (stackinfo_t){STACKINFO_OK, id, count, NULL};
}
