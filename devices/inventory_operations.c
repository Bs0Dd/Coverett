#include "../coverett.h"


const result_t IOINC = {CO_ERROR, 0, NULL, NULL, "Incorrect device type"};

int isInvOp(device_t* dev){
	return strcmp(dev->devType, "oc2r:inventory_operations_module") == 0;
}

result_t commonItems(device_t* dev, int count, char* side, char* method){
	if (!isInvOp(dev)) return IOINC;
	double numparams[] = {count};
	if (side == NULL){
		cotypes_t packord[] = {CO_NUMBER};
		uniInvoke(dev, method, numparams, NULL, 1, packord);
	}
	cotypes_t packord[] = {CO_NUMBER, CO_STRING};
	char* strparams[] = {side};
	result_t res = uniInvoke(dev, method, numparams, strparams, 2, packord);
	if (res.type == CO_ERROR && strcmp(res.errString, "IllegalArgumentException") == 0){
		free(res.errString);
		res.errString = "Incorrect side";
	}
	return res;
}

result_t commonInFr(device_t* dev, int into, int count, char* side, char* method){
	if (!isInvOp(dev)) return IOINC;
	double numparams[] = {into, count};
	if (side == NULL){
		cotypes_t packord[] = {CO_NUMBER, CO_NUMBER};
		uniInvoke(dev, method, numparams, NULL, 2, packord);
	}
	cotypes_t packord[] = {CO_NUMBER, CO_NUMBER, CO_STRING};
	char* strparams[] = {side};
	result_t res = uniInvoke(dev, method, numparams, strparams, 3, packord);
	if (res.type == CO_ERROR && strcmp(res.errString, "IllegalArgumentException") == 0){
		free(res.errString);
		res.errString = "Incorrect side";
	}
	return res;
}



result_t moveItems(device_t* device, int from, int to, int count){
	if (!isInvOp(device)) return IOINC;
	double numparams[] = {from, to, count};
	cotypes_t packord[] = {CO_NUMBER, CO_NUMBER, CO_NUMBER};
	return uniInvoke(device, "move", numparams, NULL, 3, packord);
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
