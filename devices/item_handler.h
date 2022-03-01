#ifndef ITEM_HANDLER_H_
#define ITEM_HANDLER_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "../coverett.h"

/**
 * @brief      Gets handler slots count.
 *
 * @param[in]  device  Pointer to device proxy (device_t structure).
 *
 * @return     result_t structure with the type of CO_NUMBER or CO_ERROR.
 */
result_t getHandlerSlotCount(device_t* device);

/**
 * @brief      Gets limit of the items in the handler slot.
 *
 * @param[in]  device  Pointer to device proxy (device_t structure).
 * @param[in]  slot    Number of the slot.
 *
 * @return     result_t structure with the type of CO_NUMBER or CO_ERROR.
 */
result_t getHandlerSlotLimit(device_t* device, int slot);

/**
 * @brief      Gets info about stack in the handler slot.
 *
 * @param[in]  device  Pointer to device proxy (device_t structure).
 * @param[in]  slot    Number of the slot.
 *
 * @return     stackinfo_t structure with the type of CO_OK or CO_EMPTY or CO_ERROR.
 */
stackinfo_t getHandlerStackInSlot(device_t* device, int slot);

#ifdef __cplusplus
}
#endif

#endif // ITEM_HANDLER_H_
