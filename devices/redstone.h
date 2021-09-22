#ifndef REDSTONE_H_
#define REDSTONE_H_

#include "../coverett-private.h"

RESULT getRedstoneInput(DEVICE* device, char* side);

RESULT getRedstoneOutput(DEVICE* device, char* side);

RESULT setRedstoneOutput(DEVICE* device, char* side, int strength);

#endif // REDSTONE_H_
