#include "../coverett.h"


result_t commonFunc(device_t* dev, char* side, char* method){
	if (strcmp(dev->devType, "oc2r:block_operations_module") != 0){
		return (result_t){CO_ERROR, 0, NULL, NULL, "Incorrect device type"};
	}
	if (side == NULL) return uniInvoke(dev, method, NULL, NULL, 0, NULL);
	char* strparams[] = {side};
	cotypes_t packord[] = {CO_STRING};
	result_t res = uniInvoke(dev, method, NULL, strparams, 1, packord);
	if (res.type == CO_ERROR && strcmp(res.errString, "IllegalArgumentException") == 0){
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
