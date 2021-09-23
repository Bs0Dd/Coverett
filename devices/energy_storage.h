#ifndef ENERGY_STORAGE_H_
#define ENERGY_STORAGE_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "../coverett-private.h"

/**
 * @brief      Gets current stored energy in the storage.
 *
 * @param[in]  device  Pointer to device proxy (DEVICE structure).
 *
 * @return     RESULT structure with the type of RESULT_NUMBER or RESULT_ERROR.
 */
RESULT getStorageEnergyStored(DEVICE* device);

/**
 * @brief      Gets maximal stored energy value of the storage.
 *
 * @param[in]  device  Pointer to device proxy (DEVICE structure).
 *
 * @return     RESULT structure with the type of RESULT_NUMBER or RESULT_ERROR.
 */
RESULT getStorageMaxEnergyStored(DEVICE* device);

/**
 * @brief      Gets the status, whether it is possible to extract energy.
 *
 * @param[in]  device  Pointer to device proxy (DEVICE structure).
 *
 * @return     RESULT structure with the type of RESULT_BOOLEAN or RESULT_ERROR.
 */
RESULT canExtract(DEVICE* device);

/**
 * @brief      Gets the status, whether it is possible to receive energy.
 *
 * @param[in]  device  Pointer to device proxy (DEVICE structure).
 *
 * @return     RESULT structure with the type of RESULT_BOOLEAN or RESULT_ERROR.
 */
RESULT canReceive(DEVICE* device);

#ifdef __cplusplus
}
#endif

#endif // ENERGY_STORAGE_H_
