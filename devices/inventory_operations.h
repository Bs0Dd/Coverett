#ifndef INVENTORY_OPERATIONS_H_
#define INVENTORY_OPERATIONS_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "../coverett-private.h"

/**
 * @brief      Moves items in inventory.
 *
 * @param[in]  device  Pointer to device proxy (DEVICE structure).
 * @param[in]  from    The slot to extract items from.
 * @param[in]  to      The slot to insert items into.
 * @param[in]  count   The number of items to move.
 *
 * @return     RESULT structure with the type of RESULT_VOID or RESULT_ERROR.
 */
RESULT moveItems(DEVICE* device, int from, int to, int count);

/**
 * @brief      Drops items from inventory.
 *
 * @param[in]  device  Pointer to device proxy (DEVICE structure).
 * @param[in]  count   The number of items to drop.
 * @param[in]  side    Name of the side, where the items will be dropped.
 *
 * @return     RESULT structure with the type of RESULT_NUMBER or RESULT_ERROR.
 */
RESULT dropItems(DEVICE* device, int count, char* side);

/**
 * @brief      Drops items from inventory to other inventory (e.g. chest).
 *
 * @param[in]  device  Pointer to device proxy (DEVICE structure).
 * @param[in]  into    The number of slot, where the items will be dropped.
 * @param[in]  count   The number of items to drop.
 * @param[in]  side    Name of the side, where the items will be dropped.
 *
 * @return     RESULT structure with the type of RESULT_NUMBER or RESULT_ERROR.
 */
RESULT dropInto(DEVICE* device, int into, int count, char* side);

/**
 * @brief      Takes items to inventory.
 *
 * @param[in]  device  Pointer to device proxy (DEVICE structure).
 * @param[in]  count   The number of items to take.
 * @param[in]  side    Name of the side, where the items will be taken.
 *
 * @return     RESULT structure with the type of RESULT_NUMBER or RESULT_ERROR.
 */
RESULT takeItems(DEVICE* device, int count, char* side);

/**
 * @brief      Takes items to inventory from other inventory (e.g. chest).
 *
 * @param[in]  device  Pointer to device proxy (DEVICE structure).
 * @param[in]  into    The number of slot, where the items will be taken.
 * @param[in]  count   The number of items to take.
 * @param[in]  side    Name of the side, where the items will be taken.
 *
 * @return     RESULT structure with the type of RESULT_NUMBER or RESULT_ERROR.
 */
RESULT takeFrom(DEVICE* device, int into, int count, char* side);

#ifdef __cplusplus
}
#endif

#endif // INVENTORY_OPERATIONS_H_
