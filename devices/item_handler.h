#ifndef ITEM_HANDLER_H_
#define ITEM_HANDLER_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "../coverett-private.h"

/**
 * @brief      Gets handler slots count.
 *
 * @param[in]  device  Pointer to device proxy (DEVICE structure).
 *
 * @return     RESULT structure with the type of RESULT_NUMBER or RESULT_ERROR.
 */
RESULT getHandlerSlotCount(DEVICE* device);

/**
 * @brief      Gets limit of the items in the handler slot.
 *
 * @param[in]  device  Pointer to device proxy (DEVICE structure).
 * @param[in]  slot    Number of the slot.
 *
 * @return     RESULT structure with the type of RESULT_NUMBER or RESULT_ERROR.
 */
RESULT getHandlerSlotLimit(DEVICE* device, int slot);

/**
 * @brief      Gets info about stack in the handler slot.
 *
 * @param[in]  device  Pointer to device proxy (DEVICE structure).
 * @param[in]  slot    Number of the slot.
 *
 * @return     STACKINFO structure with the type of STACKINFO_OK or STACKINFO_EMPTY or STACKINFO_ERROR.
 */
STACKINFO getHandlerStackInSlot(DEVICE* device, int slot);

#ifdef __cplusplus
}
#endif

#endif // ITEM_HANDLER_H_
