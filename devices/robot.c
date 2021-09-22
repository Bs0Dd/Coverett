#include "../coverett-private.h"
#include "../coverett.h"
#include <unistd.h>


const RESULT ROINC = {RESULT_ERROR, 0, NULL, NULL, "Incorrect device type"};

int isRobot(DEVICE* dev){
	if (strcmp(dev->devType, "robot") != 0){
		return 0;
	}
	return 1;
}

RESULT commonNoArgs(DEVICE* dev, char* method){
	if (!isRobot(dev)) return ROINC;
	return universalInvoker(dev, method, NULL, NULL, 0, NULL);
}

RESULT commonNum(DEVICE* dev, char* method, int num){
	if (!isRobot(dev)) return ROINC;
	int numparams[] = {num};
	int packord[] = {0};
	return universalInvoker(dev, method, numparams, NULL, 1, packord);
}



RESULT getEnergyStored(DEVICE* device){
	return commonNoArgs(device, "getEnergyStored");
}

RESULT getEnergyCapacity(DEVICE* device){
	return commonNoArgs(device, "getEnergyCapacity");
}

RESULT getSelectedSlot(DEVICE* device){
	return commonNoArgs(device, "getSelectedSlot");
}

RESULT setSelectedSlot(DEVICE* device, int slot){
	return commonNum(device, "setSelectedSlot", slot);
}

STACKINFO getStackInSlot(DEVICE* device, int slot){
	RESULT res = commonNum(device, "getStackInSlot", slot);
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

RESULT getLastActionId(DEVICE* device){
	return commonNoArgs(device, "getLastActionId");
}

RESULT getQueuedActionCount(DEVICE* device){
	return commonNoArgs(device, "getQueuedActionCount");
}

RESULT getActionResult(DEVICE* device, int actionId){
	return commonNum(device, "getActionResult", actionId);
}



RESULT commonAsync(DEVICE* dev, char* method, char* direction){
	if (!isRobot(dev)) return ROINC;
	char* strparams[] = {direction};
	int packord[] = {1};
	RESULT res = universalInvoker(dev, method, NULL, strparams, 1, packord);
	while (res.type == RESULT_BOOLEAN && !res.retNumber){
		usleep(100000);
		res = universalInvoker(dev, method, NULL, strparams, 1, packord);
	}
	if (res.type == RESULT_ERROR && strcmp(res.errString, "IllegalArgumentException") == 0){
		free(res.errString);
		res.errString = "Incorrect side";
	}
	return res;
}

RESULT commonSync(DEVICE* dev, char* method, char* direction){
	RESULT res = commonAsync(dev, method, direction);
	if (res.type == RESULT_ERROR && strcmp(res.errString, "IllegalArgumentException") == 0){
		free(res.errString);
		res.errString = "Incorrect side";
		return res;
	}
	RESULT id = getLastActionId(dev);
	RESULT compl = getActionResult(dev, id.retNumber);
	while (strcmp(compl.retString, "INCOMPLETE") == 0){
		free(compl.retString);
		usleep(100000);
		compl = getActionResult(dev, id.retNumber);
	}
	free(compl.retString);
	return (RESULT){RESULT_BOOLEAN, 1, NULL, NULL, NULL};
}



RESULT moveAsync(DEVICE* device, char* direction){
	return commonAsync(device, "move", direction);
}

RESULT turnAsync(DEVICE* device, char* direction){
	return commonAsync(device, "turn", direction);
}

RESULT moveSync(DEVICE* device, char* direction){
	return commonSync(device, "move", direction);
}

RESULT turnSync(DEVICE* device, char* direction){
	return commonSync(device, "turn", direction);
}
