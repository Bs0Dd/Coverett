#include "../coverett-private.h"
#include "../coverett.h"
#include <unistd.h>


const result_t ROINC = {RESULT_ERROR, 0, NULL, NULL, "Incorrect device type"};

int isRobot(device_t* dev){
	if (strcmp(dev->devType, "robot") != 0){
		return 0;
	}
	return 1;
}

result_t commonNoArgs(device_t* dev, char* method){
	if (!isRobot(dev)) return ROINC;
	return universalInvoker(dev, method, NULL, NULL, 0, NULL);
}

result_t commonNum(device_t* dev, char* method, int num){
	if (!isRobot(dev)) return ROINC;
	int numparams[] = {num};
	int packord[] = {0};
	return universalInvoker(dev, method, numparams, NULL, 1, packord);
}



result_t getEnergyStored(device_t* device){
	return commonNoArgs(device, "getEnergyStored");
}

result_t getEnergyCapacity(device_t* device){
	return commonNoArgs(device, "getEnergyCapacity");
}

result_t getSelectedSlot(device_t* device){
	return commonNoArgs(device, "getSelectedSlot");
}

result_t setSelectedSlot(device_t* device, int slot){
	return commonNum(device, "setSelectedSlot", slot);
}

stackinfo_t getStackInSlot(device_t* device, int slot){
	result_t res = commonNum(device, "getStackInSlot", slot);
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

result_t getLastActionId(device_t* device){
	return commonNoArgs(device, "getLastActionId");
}

result_t getQueuedActionCount(device_t* device){
	return commonNoArgs(device, "getQueuedActionCount");
}

result_t getActionResult(device_t* device, int actionId){
	return commonNum(device, "getActionResult", actionId);
}



result_t commonAsync(device_t* dev, char* method, char* direction){
	if (!isRobot(dev)) return ROINC;
	char* strparams[] = {direction};
	int packord[] = {1};
	result_t res = universalInvoker(dev, method, NULL, strparams, 1, packord);
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

result_t commonSync(device_t* dev, char* method, char* direction){
	result_t res = commonAsync(dev, method, direction);
	if (res.type == RESULT_ERROR && strcmp(res.errString, "IllegalArgumentException") == 0){
		free(res.errString);
		res.errString = "Incorrect side";
		return res;
	}
	result_t id = getLastActionId(dev);
	result_t compl = getActionResult(dev, id.retNumber);
	while (strcmp(compl.retString, "INCOMPLETE") == 0){
		free(compl.retString);
		usleep(100000);
		compl = getActionResult(dev, id.retNumber);
	}
	free(compl.retString);
	return (result_t){RESULT_BOOLEAN, 1, NULL, NULL, NULL};
}



result_t moveAsync(device_t* device, char* direction){
	return commonAsync(device, "move", direction);
}

result_t turnAsync(device_t* device, char* direction){
	return commonAsync(device, "turn", direction);
}

result_t moveSync(device_t* device, char* direction){
	return commonSync(device, "move", direction);
}

result_t turnSync(device_t* device, char* direction){
	return commonSync(device, "turn", direction);
}
