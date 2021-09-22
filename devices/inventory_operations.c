#include "../coverett-private.h"
#include "../coverett.h"


const RESULT IOINC = {RESULT_ERROR, 0, NULL, NULL, "Incorrect device type"};

int isInvOp(DEVICE* dev){
	if (strcmp(dev->devType, "oc2:inventory_operations_module") != 0){
		return 0;
	}
	return 1;
}

RESULT commonItems(DEVICE* dev, int count, char* side, char* method){
	if (!isInvOp(dev)) return IOINC;
	int numparams[] = {count};
	if (side == NULL){
		int packord[] = {0};
		universalInvoker(dev, method, numparams, NULL, 1, packord);
	}
	int packord[] = {0, 1};
	char* strparams[] = {side};
	RESULT res = universalInvoker(dev, method, numparams, strparams, 2, packord);
	if (res.type == RESULT_ERROR && strcmp(res.errString, "IllegalArgumentException") == 0){
		free(res.errString);
		res.errString = "Incorrect side";
	}
	return res;
}

RESULT commonInFr(DEVICE* dev, int into, int count, char* side, char* method){
	if (!isInvOp(dev)) return IOINC;
	int numparams[] = {into, count};
	if (side == NULL){
		int packord[] = {0, 0};
		universalInvoker(dev, method, numparams, NULL, 2, packord);
	}
	int packord[] = {0, 0, 1};
	char* strparams[] = {side};
	RESULT res = universalInvoker(dev, method, numparams, strparams, 3, packord);
	if (res.type == RESULT_ERROR && strcmp(res.errString, "IllegalArgumentException") == 0){
		free(res.errString);
		res.errString = "Incorrect side";
	}
	return res;
}



RESULT moveItems(DEVICE* device, int from, int to, int count){
	if (!isInvOp(device)) return IOINC;
	int numparams[] = {from, to, count};
	int packord[] = {0, 0, 0};
	return universalInvoker(device, "move", numparams, NULL, 3, packord);
}

RESULT dropItems(DEVICE* device, int count, char* side){
	return commonItems(device, count, side, "drop");
}

RESULT dropInto(DEVICE* device, int into, int count, char* side){
	return commonInFr(device, into, count, side, "dropInto");
}

RESULT takeItems(DEVICE* device, int count, char* side){
	return commonItems(device, count, side, "take");
}

RESULT takeFrom(DEVICE* device, int into, int count, char* side){
	return commonInFr(device, into, count, side, "takeFrom");
}
