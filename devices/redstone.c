#include "../coverett-private.h"
#include "../coverett.h"


result_t baseFunc(device_t* device, char* side, char* methname, int* numparams, int nofpar, int* packord){
	if (strcmp(device->devType, "oc2:redstone_interface") != 0){
		return (result_t){RESULT_ERROR, 0, NULL, NULL, "Incorrect device type"};
	}
	char* strparams[] = {side};
	result_t res = universalInvoker(device, methname, numparams, strparams, nofpar, packord);
	if (res.type == RESULT_ERROR && strcmp(res.errString, "IllegalArgumentException") == 0){
		free(res.errString);
		res.errString = "Incorrect side";
	}
	return res;
}



result_t getRedstoneInput(device_t* device, char* side){
	int packord[] = {1};
	return baseFunc(device, side, "getRedstoneInput", NULL, 1, packord);
}

result_t getRedstoneOutput(device_t* device, char* side){
	int packord[] = {1};
	return baseFunc(device, side, "getRedstoneOutput", NULL, 1, packord);
}

result_t setRedstoneOutput(device_t* device, char* side, int strength){
	int packord[] = {1, 0};
	int intparams[] = {strength};
	return baseFunc(device, side, "setRedstoneOutput", intparams, 2, packord);
}
