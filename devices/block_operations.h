#ifndef BLOCK_OPERATIONS_H_
#define BLOCK_OPERATIONS_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "../coverett-private.h"

/**
 * @brief      Tries to break the block.
 *
 * @param[in]  device  Pointer to device proxy (DEVICE structure).
 * @param[in]  side    Name of the side, where block will be breaked.
 *
 * @return     RESULT structure with the type of RESULT_BOOLEAN or RESULT_ERROR.
 */
RESULT excavate(DEVICE* device, char* side);

/**
 * @brief      Tries to place the block.
 *
 * @param[in]  device  Pointer to device proxy (DEVICE structure).
 * @param[in]  side    Name of the side, where block will be placed.
 *
 * @return     RESULT structure with the type of RESULT_BOOLEAN or RESULT_ERROR.
 */
RESULT place(DEVICE* device, char* side);

/**
 * @brief      Gets the remaining durability of the module.
 *
 * @param[in]  device  Pointer to device proxy (DEVICE structure).
 *
 * @return     RESULT structure with the type of RESULT_NUMBER or RESULT_ERROR.
 */
RESULT durability(DEVICE* device);

/**
 * @brief      Tries to repair the module.
 *
 * @param[in]  device  Pointer to device proxy (DEVICE structure).
 *
 * @return     RESULT structure with the type of RESULT_BOOLEAN or RESULT_ERROR.
 */
RESULT repair(DEVICE* device);

#ifdef __cplusplus
}
#endif

#endif // BLOCK_OPERATIONS_H_
