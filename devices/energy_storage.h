#ifndef ENERGY_STORAGE_H_
#define ENERGY_STORAGE_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "../coverett-private.h"

RESULT getStorageEnergyStored(DEVICE* device);

RESULT getStorageMaxEnergyStored(DEVICE* device);

RESULT canExtract(DEVICE* device);

RESULT canReceive(DEVICE* device);

#ifdef __cplusplus
}
#endif

#endif // ENERGY_STORAGE_H_
