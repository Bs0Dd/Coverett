#ifndef INVENTORY_OPERATIONS_H_
#define INVENTORY_OPERATIONS_H_

#include "../coverett-private.h"

RESULT moveItems(DEVICE* device, int from, int to, int count);

RESULT dropItems(DEVICE* device, int count, char* side);

RESULT dropInto(DEVICE* device, int into, int count, char* side);

RESULT takeItems(DEVICE* device, int count, char* side);

RESULT takeFrom(DEVICE* device, int into, int count, char* side);

#endif // INVENTORY_OPERATIONS_H_
