#ifndef ROBOT_H_
#define ROBOT_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "../coverett-private.h"

/**
 * @brief      Gets current stored energy in the robot.
 *
 * @param[in]  device  Pointer to device proxy (DEVICE structure).
 *
 * @return     RESULT structure with the type of RESULT_NUMBER or RESULT_ERROR.
 */
RESULT getEnergyStored(DEVICE* device);

/**
 * @brief      Gets maximal stored energy value of the robot.
 *
 * @param[in]  device  Pointer to device proxy (DEVICE structure).
 *
 * @return     RESULT structure with the type of RESULT_NUMBER or RESULT_ERROR.
 */
RESULT getEnergyCapacity(DEVICE* device);

/**
 * @brief      Gets the number of currently selected slot.
 *
 * @param[in]  device  Pointer to device proxy (DEVICE structure).
 *
 * @return     RESULT structure with the type of RESULT_NUMBER or RESULT_ERROR.
 */
RESULT getSelectedSlot(DEVICE* device);

/**
 * @brief      Sets selected slot.
 *
 * @param[in]  device  Pointer to device proxy (DEVICE structure).
 * @param[in]  slot    Slot number to set.
 *
 * @return     RESULT structure with the type of RESULT_NUMBER or RESULT_ERROR.
 */
RESULT setSelectedSlot(DEVICE* device, int slot);

/**
 * @brief      Gets info about stack in the slot.
 *
 * @param[in]  device  Pointer to device proxy (DEVICE structure).
 * @param[in]  slot    Number of the slot.
 *
 * @return     STACKINFO structure with the type of STACKINFO_OK or STACKINFO_EMPTY or STACKINFO_ERROR.
 */
STACKINFO getStackInSlot(DEVICE* device, int slot);

/**
 * @brief      Gets id of the last action.
 *
 * @param[in]  device  Pointer to device proxy (DEVICE structure).
 *
 * @return     RESULT structure with the type of RESULT_NUMBER or RESULT_ERROR.
 */
RESULT getLastActionId(DEVICE* device);

/**
 * @brief      Gets the count of the actions in queue.
 *
 * @param[in]  device  Pointer to device proxy (DEVICE structure).
 *
 * @return     RESULT structure with the type of RESULT_NUMBER or RESULT_ERROR.
 */
RESULT getQueuedActionCount(DEVICE* device);

/**
 * @brief      Gets the result of the action by its ID.
 *
 * @param[in]  device    Pointer to device proxy (DEVICE structure).
 * @param[in]  actionId  ID of the action.
 *
 * @return     RESULT structure with the type of RESULT_STRING or RESULT_ERROR.
 */
RESULT getActionResult(DEVICE* device, int actionId);

/**
 * @brief      Attempts to move asynchronously.
 *
 * @param[in]  device     Pointer to device proxy (DEVICE structure).
 * @param[in]  direction  Name of the direction.
 *
 * @return     RESULT structure with the type of RESULT_BOOLEAN or RESULT_ERROR.
 */
RESULT moveAsync(DEVICE* device, char* direction);

/**
 * @brief      Attempts to turn asynchronously.
 *
 * @param[in]  device     Pointer to device proxy (DEVICE structure).
 * @param[in]  direction  Name of the direction.
 *
 * @return     RESULT structure with the type of RESULT_BOOLEAN or RESULT_ERROR.
 */
RESULT turnAsync(DEVICE* device, char* direction);

/**
 * @brief      Attempts to move synchronously.
 *
 * @param[in]  device     Pointer to device proxy (DEVICE structure).
 * @param[in]  direction  Name of the direction.
 *
 * @return     RESULT structure with the type of RESULT_BOOLEAN or RESULT_ERROR.
 */
RESULT moveSync(DEVICE* device, char* direction);

/**
 * @brief      Attempts to turn synchronously.
 *
 * @param[in]  device     Pointer to device proxy (DEVICE structure).
 * @param[in]  direction  Name of the direction.
 *
 * @return     RESULT structure with the type of RESULT_BOOLEAN or RESULT_ERROR.
 */
RESULT turnSync(DEVICE* device, char* direction);

#ifdef __cplusplus
}
#endif

#endif // ROBOT_H_
