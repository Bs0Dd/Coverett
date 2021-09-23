#ifndef ROBOT_H_
#define ROBOT_H_

#ifdef __cplusplus
extern "C"{
#endif

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

#ifdef __cplusplus
}
#endif

#endif // ROBOT_H_
