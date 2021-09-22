#include "../coverett-private.h"
#include "../coverett.h"


int isEnStor(DEVICE* dev){
	if (strcmp(dev->devType, "oc2:computer") != 0){
		return 0;
	}
	return 1;
}

RESULT commonStNoArgs(DEVICE* dev, char* method){
	if (!isEnStor(dev)) return (RESULT){RESULT_ERROR, 0, NULL, NULL, "Incorrect device type"};
	return universalInvoker(dev, method, NULL, NULL, 0, NULL);
}



RESULT getStorageEnergyStored(DEVICE* device){
	return commonStNoArgs(device, "getEnergyStored");
}

RESULT getStorageMaxEnergyStored(DEVICE* device){
	return commonStNoArgs(device, "getMaxEnergyStored");
}

RESULT canExtract(DEVICE* device){
	return commonStNoArgs(device, "canExtract");
}

RESULT canReceive(DEVICE* device){
	return commonStNoArgs(device, "canReceive");
}
