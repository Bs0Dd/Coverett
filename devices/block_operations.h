#ifndef BLOCK_OPERATIONS_H_
#define BLOCK_OPERATIONS_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "../coverett-private.h"

RESULT excavate(DEVICE* device, char* side);

RESULT place(DEVICE* device, char* side);

RESULT durability(DEVICE* device);

RESULT repair(DEVICE* device);

#ifdef __cplusplus
}
#endif

#endif // BLOCK_OPERATIONS_H_
