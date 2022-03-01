#ifndef BLOCK_OPERATIONS_H_
#define BLOCK_OPERATIONS_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "../coverett.h"

/**
 * @brief      Tries to break the block.
 *
 * @param[in]  device  Pointer to device proxy (device_t structure).
 * @param[in]  side    Name of the side, where block will be breaked.
 *
 * @return     result_t structure with the type of CO_BOOLEAN or CO_ERROR.
 */
result_t excavate(device_t* device, char* side);

/**
 * @brief      Tries to place the block.
 *
 * @param[in]  device  Pointer to device proxy (device_t structure).
 * @param[in]  side    Name of the side, where block will be placed.
 *
 * @return     result_t structure with the type of CO_BOOLEAN or CO_ERROR.
 */
result_t place(device_t* device, char* side);

/**
 * @brief      Gets the remaining durability of the module.
 *
 * @param[in]  device  Pointer to device proxy (device_t structure).
 *
 * @return     result_t structure with the type of CO_NUMBER or CO_ERROR.
 */
result_t durability(device_t* device);

/**
 * @brief      Tries to repair the module.
 *
 * @param[in]  device  Pointer to device proxy (device_t structure).
 *
 * @return     result_t structure with the type of CO_BOOLEAN or CO_ERROR.
 */
result_t repair(device_t* device);

#ifdef __cplusplus
}
#endif

#endif // BLOCK_OPERATIONS_H_
