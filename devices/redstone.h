#ifndef REDSTONE_H_
#define REDSTONE_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "../coverett.h"

/**
 * @brief      Gets current signal strength from the input.
 *
 * @param[in]  device  Pointer to device proxy (device_t structure).
 * @param[in]  side    Name of the input side.
 *
 * @return     result_t structure with the type of CO_NUMBER or CO_ERROR.
 */
result_t getRedstoneInput(device_t* device, char* side);

/**
 * @brief      Gets current signal strength from the output.
 *
 * @param[in]  device  Pointer to device proxy (device_t structure).
 * @param[in]  side    Name of the output side.
 *
 * @return     result_t structure with the type of CO_NUMBER or CO_ERROR.
 */
result_t getRedstoneOutput(device_t* device, char* side);

/**
 * @brief      Sets output signal strength.
 *
 * @param[in]  device    Pointer to device proxy (device_t structure).
 * @param[in]  side      Name of the output side.
 * @param[in]  strength  Strength value to set.
 *
 * @return     result_t structure with the type of CO_VOID or CO_ERROR.
 */
result_t setRedstoneOutput(device_t* device, char* side, int strength);

#ifdef __cplusplus
}
#endif

#endif // REDSTONE_H_
