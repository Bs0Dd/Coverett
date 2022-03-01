#ifndef ROBOT_H_
#define ROBOT_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "../coverett.h"

/**
 * @brief      Gets current stored energy in the robot.
 *
 * @param[in]  device  Pointer to device proxy (device_t structure).
 *
 * @return     result_t structure with the type of CO_NUMBER or CO_ERROR.
 */
result_t getEnergyStored(device_t* device);

/**
 * @brief      Gets maximal stored energy value of the robot.
 *
 * @param[in]  device  Pointer to device proxy (device_t structure).
 *
 * @return     result_t structure with the type of CO_NUMBER or CO_ERROR.
 */
result_t getEnergyCapacity(device_t* device);

/**
 * @brief      Gets the number of currently selected slot.
 *
 * @param[in]  device  Pointer to device proxy (device_t structure).
 *
 * @return     result_t structure with the type of CO_NUMBER or CO_ERROR.
 */
result_t getSelectedSlot(device_t* device);

/**
 * @brief      Sets selected slot.
 *
 * @param[in]  device  Pointer to device proxy (device_t structure).
 * @param[in]  slot    Slot number to set.
 *
 * @return     result_t structure with the type of CO_NUMBER or CO_ERROR.
 */
result_t setSelectedSlot(device_t* device, int slot);

/**
 * @brief      Gets info about stack in the slot.
 *
 * @param[in]  device  Pointer to device proxy (device_t structure).
 * @param[in]  slot    Number of the slot.
 *
 * @return     stackinfo_t structure with the type of CO_OK or CO_EMPTY or CO_ERROR.
 */
stackinfo_t getStackInSlot(device_t* device, int slot);

/**
 * @brief      Gets id of the last action.
 *
 * @param[in]  device  Pointer to device proxy (device_t structure).
 *
 * @return     result_t structure with the type of CO_NUMBER or CO_ERROR.
 */
result_t getLastActionId(device_t* device);

/**
 * @brief      Gets the count of the actions in queue.
 *
 * @param[in]  device  Pointer to device proxy (device_t structure).
 *
 * @return     result_t structure with the type of CO_NUMBER or CO_ERROR.
 */
result_t getQueuedActionCount(device_t* device);

/**
 * @brief      Gets the result of the action by its ID.
 *
 * @param[in]  device    Pointer to device proxy (device_t structure).
 * @param[in]  actionId  ID of the action.
 *
 * @return     result_t structure with the type of CO_STRING or CO_ERROR.
 */
result_t getActionResult(device_t* device, int actionId);

/**
 * @brief      Attempts to move asynchronously.
 *
 * @param[in]  device     Pointer to device proxy (device_t structure).
 * @param[in]  direction  Name of the direction.
 *
 * @return     result_t structure with the type of CO_BOOLEAN or CO_ERROR.
 */
result_t moveAsync(device_t* device, char* direction);

/**
 * @brief      Attempts to turn asynchronously.
 *
 * @param[in]  device     Pointer to device proxy (device_t structure).
 * @param[in]  direction  Name of the direction.
 *
 * @return     result_t structure with the type of CO_BOOLEAN or CO_ERROR.
 */
result_t turnAsync(device_t* device, char* direction);

/**
 * @brief      Attempts to move synchronously.
 *
 * @param[in]  device     Pointer to device proxy (device_t structure).
 * @param[in]  direction  Name of the direction.
 *
 * @return     result_t structure with the type of CO_BOOLEAN or CO_ERROR.
 */
result_t moveSync(device_t* device, char* direction);

/**
 * @brief      Attempts to turn synchronously.
 *
 * @param[in]  device     Pointer to device proxy (device_t structure).
 * @param[in]  direction  Name of the direction.
 *
 * @return     result_t structure with the type of CO_BOOLEAN or CO_ERROR.
 */
result_t turnSync(device_t* device, char* direction);

#ifdef __cplusplus
}
#endif

#endif // ROBOT_H_
