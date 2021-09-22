#include "../coverett-private.h"
#include "../coverett.h"


const RESULT IHINC = {RESULT_ERROR, 0, NULL, NULL, "Incorrect device type"};

int isItHand(DEVICE* dev){
	if (strcmp(dev->devType, "oc2:computer") != 0 || strcmp(dev->devType, "oc2:disk_drive") != 0){
		return 0;
	}
	return 1;
}



RESULT getHandlerSlotCount(DEVICE* device){
	if (!isItHand(device)) return IHINC;
	return universalInvoker(device, "getSlotCount", NULL, NULL, 0, NULL);
}

RESULT getHandlerSlotLimit(DEVICE* device, int slot){ // a slot? idk, in methods list this is named as "arg1", so it maybe not a slot
	if (!isItHand(device)) return IHINC;
	int numparams[] = {slot};
	int packord[] = {0};
	return universalInvoker(device, "getSlotLimit", numparams, NULL, 1, packord);
}

STACKINFO getHandlerStackInSlot(DEVICE* device, int slot){ // a slot? idk, in methods list this is named as "arg1", so it maybe not a slot
	if (!isItHand(device)) return (STACKINFO){STACKINFO_ERROR, NULL, 0, IHINC.errString};
	int numparams[] = {slot};
	int packord[] = {0};
	RESULT res = universalInvoker(device, "getStackInSlot", numparams, NULL, 1, packord);
	if (res.type == RESULT_ERROR){
		return (STACKINFO){STACKINFO_ERROR, NULL, 0, res.errString};
	}
	else if (res.type == RESULT_VOID){
		return (STACKINFO){STACKINFO_EMPTY, NULL, 0, NULL};
	}
	char* id = strdup(cJSON_GetObjectItemCaseSensitive(res.retList, "id")->valuestring);
	int count = cJSON_GetObjectItemCaseSensitive(res.retList, "Count")->valueint;
	cJSON_Delete(res.retList);
	return (STACKINFO){STACKINFO_OK, id, count, NULL};
}
