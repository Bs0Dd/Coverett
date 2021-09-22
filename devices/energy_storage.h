#ifndef ENERGY_STORAGE_H_
#define ENERGY_STORAGE_H_

#include "../coverett-private.h"

RESULT getStorageEnergyStored(DEVICE* device);

RESULT getStorageMaxEnergyStored(DEVICE* device);

RESULT canExtract(DEVICE* device);

RESULT canReceive(DEVICE* device);

#endif // ENERGY_STORAGE_H_
