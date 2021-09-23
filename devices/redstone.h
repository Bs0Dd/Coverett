#ifndef REDSTONE_H_
#define REDSTONE_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "../coverett-private.h"

/**
 * @brief      Gets current signal strength from the input.
 *
 * @param[in]  device  Pointer to device proxy (DEVICE structure).
 * @param[in]  side    Name of the input side.
 *
 * @return     RESULT structure with the type of RESULT_NUMBER or RESULT_ERROR.
 */
RESULT getRedstoneInput(DEVICE* device, char* side);

/**
 * @brief      Gets current signal strength from the output.
 *
 * @param[in]  device  Pointer to device proxy (DEVICE structure).
 * @param[in]  side    Name of the output side.
 *
 * @return     RESULT structure with the type of RESULT_NUMBER or RESULT_ERROR.
 */
RESULT getRedstoneOutput(DEVICE* device, char* side);

/**
 * @brief      Sets output signal strength.
 *
 * @param[in]  device    Pointer to device proxy (DEVICE structure).
 * @param[in]  side      Name of the output side.
 * @param[in]  strength  Strength value to set.
 *
 * @return     RESULT structure with the type of RESULT_VOID or RESULT_ERROR.
 */
RESULT setRedstoneOutput(DEVICE* device, char* side, int strength);

#ifdef __cplusplus
}
#endif

#endif // REDSTONE_H_
