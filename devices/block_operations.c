#include "../coverett-private.h"
#include "../coverett.h"


int isBlockOp(DEVICE* dev){
	if (strcmp(dev->devType, "oc2:block_operations_module") != 0){
		return 0;
	}
	return 1;
}

RESULT commonFunc(DEVICE* dev, char* side, char* method){
	if (!isBlockOp(dev)) return (RESULT){RESULT_ERROR, 0, NULL, NULL, "Incorrect device type"};
	if (side == NULL) return universalInvoker(dev, method, NULL, NULL, 0, NULL);
	char* strparams[] = {side};
	int packord[] = {1};
	RESULT res = universalInvoker(dev, method, NULL, strparams, 1, packord);
	if (res.type == RESULT_ERROR && strcmp(res.errString, "IllegalArgumentException") == 0){
		free(res.errString);
		res.errString = "Incorrect side";
	}
	return res;
}



RESULT excavate(DEVICE* device, char* side){
	return commonFunc(device, side, "excavate");
}

RESULT place(DEVICE* device, char* side){
	return commonFunc(device, side, "place");
}

RESULT durability(DEVICE* device){
	return commonFunc(device, NULL, "durability");
}

RESULT repair(DEVICE* device){
	return commonFunc(device, NULL, "repair");
}
