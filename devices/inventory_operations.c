#include "../coverett-private.h"
#include "../coverett.h"


const result_t IOINC = {RESULT_ERROR, 0, NULL, NULL, "Incorrect device type"};

int isInvOp(device_t* dev){
	if (strcmp(dev->devType, "oc2:inventory_operations_module") != 0){
		return 0;
	}
	return 1;
}

result_t commonItems(device_t* dev, int count, char* side, char* method){
	if (!isInvOp(dev)) return IOINC;
	int numparams[] = {count};
	if (side == NULL){
		int packord[] = {0};
		universalInvoker(dev, method, numparams, NULL, 1, packord);
	}
	int packord[] = {0, 1};
	char* strparams[] = {side};
	result_t res = universalInvoker(dev, method, numparams, strparams, 2, packord);
	if (res.type == RESULT_ERROR && strcmp(res.errString, "IllegalArgumentException") == 0){
		free(res.errString);
		res.errString = "Incorrect side";
	}
	return res;
}

result_t commonInFr(device_t* dev, int into, int count, char* side, char* method){
	if (!isInvOp(dev)) return IOINC;
	int numparams[] = {into, count};
	if (side == NULL){
		int packord[] = {0, 0};
		universalInvoker(dev, method, numparams, NULL, 2, packord);
	}
	int packord[] = {0, 0, 1};
	char* strparams[] = {side};
	result_t res = universalInvoker(dev, method, numparams, strparams, 3, packord);
	if (res.type == RESULT_ERROR && strcmp(res.errString, "IllegalArgumentException") == 0){
		free(res.errString);
		res.errString = "Incorrect side";
	}
	return res;
}



result_t moveItems(device_t* device, int from, int to, int count){
	if (!isInvOp(device)) return IOINC;
	int numparams[] = {from, to, count};
	int packord[] = {0, 0, 0};
	return universalInvoker(device, "move", numparams, NULL, 3, packord);
}

result_t dropItems(device_t* device, int count, char* side){
	return commonItems(device, count, side, "drop");
}

result_t dropInto(device_t* device, int into, int count, char* side){
	return commonInFr(device, into, count, side, "dropInto");
}

result_t takeItems(device_t* device, int count, char* side){
	return commonItems(device, count, side, "take");
}

result_t takeFrom(device_t* device, int into, int count, char* side){
	return commonInFr(device, into, count, side, "takeFrom");
}
