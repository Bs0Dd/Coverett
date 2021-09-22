#include "../coverett-private.h"
#include "../coverett.h"


RESULT baseFunc(DEVICE* device, char* side, char* methname, int* numparams, int nofpar, int* packord){
	if (strcmp(device->devType, "oc2:redstone_interface") != 0){
		return (RESULT){RESULT_ERROR, 0, NULL, NULL, "Incorrect device type"};
	}
	char* strparams[] = {side};
	RESULT res = universalInvoker(device, methname, numparams, strparams, nofpar, packord);
	if (res.type == RESULT_ERROR && strcmp(res.errString, "IllegalArgumentException") == 0){
		free(res.errString);
		res.errString = "Incorrect side";
	}
	return res;
}



RESULT getRedstoneInput(DEVICE* device, char* side){
	int packord[] = {1};
	return baseFunc(device, side, "getRedstoneInput", NULL, 1, packord);
}

RESULT getRedstoneOutput(DEVICE* device, char* side){
	int packord[] = {1};
	return baseFunc(device, side, "getRedstoneOutput", NULL, 1, packord);
}

RESULT setRedstoneOutput(DEVICE* device, char* side, int strength){
	int packord[] = {1, 0};
	int intparams[] = {strength};
	return baseFunc(device, side, "setRedstoneOutput", intparams, 2, packord);
}
