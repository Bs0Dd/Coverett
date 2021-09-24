#include "../coverett-private.h"
#include "../coverett.h"


int isBlockOp(device_t* dev){
	if (strcmp(dev->devType, "oc2:block_operations_module") != 0){
		return 0;
	}
	return 1;
}

result_t commonFunc(device_t* dev, char* side, char* method){
	if (!isBlockOp(dev)) return (result_t){RESULT_ERROR, 0, NULL, NULL, "Incorrect device type"};
	if (side == NULL) return universalInvoker(dev, method, NULL, NULL, 0, NULL);
	char* strparams[] = {side};
	int packord[] = {1};
	result_t res = universalInvoker(dev, method, NULL, strparams, 1, packord);
	if (res.type == RESULT_ERROR && strcmp(res.errString, "IllegalArgumentException") == 0){
		free(res.errString);
		res.errString = "Incorrect side";
	}
	return res;
}



result_t excavate(device_t* device, char* side){
	return commonFunc(device, side, "excavate");
}

result_t place(device_t* device, char* side){
	return commonFunc(device, side, "place");
}

result_t durability(device_t* device){
	return commonFunc(device, NULL, "durability");
}

result_t repair(device_t* device){
	return commonFunc(device, NULL, "repair");
}
