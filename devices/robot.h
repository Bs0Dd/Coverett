#ifndef ROBOT_H_
#define ROBOT_H_

#include "../coverett-private.h"

RESULT getEnergyStored(DEVICE* device);

RESULT getEnergyCapacity(DEVICE* device);

RESULT getSelectedSlot(DEVICE* device);

RESULT setSelectedSlot(DEVICE* device, int slot);

STACKINFO getStackInSlot(DEVICE* device, int slot);

RESULT getLastActionId(DEVICE* device);

RESULT getQueuedActionCount(DEVICE* device);

RESULT getActionResult(DEVICE* device, int actionId);

RESULT moveAsync(DEVICE* device, char* direction);

RESULT turnAsync(DEVICE* device, char* direction);

RESULT moveSync(DEVICE* device, char* direction);

RESULT turnSync(DEVICE* device, char* direction);

#endif // ROBOT_H_
