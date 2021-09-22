#ifndef ITEM_HANDLER_H_
#define ITEM_HANDLER_H_

#include "../coverett-private.h"

RESULT getHandlerSlotCount(DEVICE* device);

RESULT getHandlerSlotLimit(DEVICE* device, int slot);

STACKINFO getHandlerStackInSlot(DEVICE* device, int slot);

#endif // ITEM_HANDLER_H_
