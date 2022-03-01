#include "../coverett.h"


result_t baseFunc(device_t* device, char* side, char* methname, double* numparams, int nofpar, int* packord){
	if (strcmp(device->devType, "oc2:redstone_interface") != 0){
		return (result_t){CO_ERROR, 0, NULL, NULL, "Incorrect device type"};
	}
	char* strparams[] = {side};
	result_t res = uniInvoke(device, methname, numparams, strparams, nofpar, packord);
	if (res.type == CO_ERROR && strcmp(res.errString, "IllegalArgumentException") == 0){
		free(res.errString);
		res.errString = "Incorrect side";
	}
	return res;
}



result_t getRedstoneInput(device_t* device, char* side){
	cotypes_t packord[] = {CO_STRING};
	return baseFunc(device, side, "getRedstoneInput", NULL, 1, packord);
}

result_t getRedstoneOutput(device_t* device, char* side){
	cotypes_t packord[] = {CO_STRING};
	return baseFunc(device, side, "getRedstoneOutput", NULL, 1, packord);
}

result_t setRedstoneOutput(device_t* device, char* side, int strength){
	cotypes_t packord[] = {CO_STRING, CO_NUMBER};
	double intparams[] = {strength};
	return baseFunc(device, side, "setRedstoneOutput", intparams, 2, packord);
}
