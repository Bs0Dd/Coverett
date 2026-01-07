#include "../coverett.h"


result_t commonStNoArgs(device_t* dev, char* method){
	if (strcmp(dev->devType, "oc2r:computer") != 0 && strcmp(dev->devType, "oc2r:projector") != 0){
		return (result_t){CO_ERROR, 0, NULL, NULL, "Incorrect device type"};
	}
	return uniInvoke(dev, method, NULL, NULL, 0, NULL);
}



result_t getStorageEnergyStored(device_t* device){
	return commonStNoArgs(device, "getEnergyStored");
}

result_t getStorageMaxEnergyStored(device_t* device){
	return commonStNoArgs(device, "getMaxEnergyStored");
}

result_t canExtract(device_t* device){
	return commonStNoArgs(device, "canExtract");
}

result_t canReceive(device_t* device){
	return commonStNoArgs(device, "canReceive");
}
