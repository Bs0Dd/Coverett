#ifndef ITEM_HANDLER_H_
#define ITEM_HANDLER_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "../coverett-private.h"

RESULT getHandlerSlotCount(DEVICE* device);

RESULT getHandlerSlotLimit(DEVICE* device, int slot);

STACKINFO getHandlerStackInSlot(DEVICE* device, int slot);

#ifdef __cplusplus
}
#endif

#endif // ITEM_HANDLER_H_
