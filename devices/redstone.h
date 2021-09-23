#ifndef REDSTONE_H_
#define REDSTONE_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "../coverett-private.h"

RESULT getRedstoneInput(DEVICE* device, char* side);

RESULT getRedstoneOutput(DEVICE* device, char* side);

RESULT setRedstoneOutput(DEVICE* device, char* side, int strength);

#ifdef __cplusplus
}
#endif

#endif // REDSTONE_H_
