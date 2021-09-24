#ifndef ENERGY_STORAGE_H_
#define ENERGY_STORAGE_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "../coverett-private.h"

/**
 * @brief      Gets current stored energy in the storage.
 *
 * @param[in]  device  Pointer to device proxy (device_t structure).
 *
 * @return     result_t structure with the type of RESULT_NUMBER or RESULT_ERROR.
 */
result_t getStorageEnergyStored(device_t* device);

/**
 * @brief      Gets maximal stored energy value of the storage.
 *
 * @param[in]  device  Pointer to device proxy (device_t structure).
 *
 * @return     result_t structure with the type of RESULT_NUMBER or RESULT_ERROR.
 */
result_t getStorageMaxEnergyStored(device_t* device);

/**
 * @brief      Gets the status, whether it is possible to extract energy.
 *
 * @param[in]  device  Pointer to device proxy (device_t structure).
 *
 * @return     result_t structure with the type of RESULT_BOOLEAN or RESULT_ERROR.
 */
result_t canExtract(device_t* device);

/**
 * @brief      Gets the status, whether it is possible to receive energy.
 *
 * @param[in]  device  Pointer to device proxy (device_t structure).
 *
 * @return     result_t structure with the type of RESULT_BOOLEAN or RESULT_ERROR.
 */
result_t canReceive(device_t* device);

#ifdef __cplusplus
}
#endif

#endif // ENERGY_STORAGE_H_
