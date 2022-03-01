#ifndef INVENTORY_OPERATIONS_H_
#define INVENTORY_OPERATIONS_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "../coverett.h"

/**
 * @brief      Moves items in inventory.
 *
 * @param[in]  device  Pointer to device proxy (device_t structure).
 * @param[in]  from    The slot to extract items from.
 * @param[in]  to      The slot to insert items into.
 * @param[in]  count   The number of items to move.
 *
 * @return     result_t structure with the type of CO_VOID or CO_ERROR.
 */
result_t moveItems(device_t* device, int from, int to, int count);

/**
 * @brief      Drops items from inventory.
 *
 * @param[in]  device  Pointer to device proxy (device_t structure).
 * @param[in]  count   The number of items to drop.
 * @param[in]  side    Name of the side, where the items will be dropped.
 *
 * @return     result_t structure with the type of CO_NUMBER or CO_ERROR.
 */
result_t dropItems(device_t* device, int count, char* side);

/**
 * @brief      Drops items from inventory to other inventory (e.g. chest).
 *
 * @param[in]  device  Pointer to device proxy (device_t structure).
 * @param[in]  into    The number of slot, where the items will be dropped.
 * @param[in]  count   The number of items to drop.
 * @param[in]  side    Name of the side, where the items will be dropped.
 *
 * @return     result_t structure with the type of CO_NUMBER or CO_ERROR.
 */
result_t dropInto(device_t* device, int into, int count, char* side);

/**
 * @brief      Takes items to inventory.
 *
 * @param[in]  device  Pointer to device proxy (device_t structure).
 * @param[in]  count   The number of items to take.
 * @param[in]  side    Name of the side, where the items will be taken.
 *
 * @return     result_t structure with the type of CO_NUMBER or CO_ERROR.
 */
result_t takeItems(device_t* device, int count, char* side);

/**
 * @brief      Takes items to inventory from other inventory (e.g. chest).
 *
 * @param[in]  device  Pointer to device proxy (device_t structure).
 * @param[in]  into    The number of slot, where the items will be taken.
 * @param[in]  count   The number of items to take.
 * @param[in]  side    Name of the side, where the items will be taken.
 *
 * @return     result_t structure with the type of CO_NUMBER or CO_ERROR.
 */
result_t takeFrom(device_t* device, int into, int count, char* side);

#ifdef __cplusplus
}
#endif

#endif // INVENTORY_OPERATIONS_H_
