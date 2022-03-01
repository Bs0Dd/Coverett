#ifndef SOUND_H_
#define SOUND_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "../coverett.h"

/**
 * @brief      Attempts to play the specified sound.
 *
 * @param[in]  device  Pointer to device proxy (device_t structure).
 * @param[in]  name    Name of the sound to play.
 *
 * @return     result_t structure with the type of CO_VOID or CO_ERROR.
 */
result_t playSound(device_t* device, char* name, double volume, double pitch);

/**
 * @brief      Finds the sounds by the string.
 *
 * @param[in]  device  Pointer to device proxy (device_t structure).
 * @param[in]  string  String to search.
 *
 * @return     list_t structure with the type of CO_SOUNDS or CO_ERROR.
 */
list_t findSound(device_t* device, char* string);

/**
 * @brief      Gets the sounds names from list.
 *
 * @param[in]  list         List of the type CO_SOUNDS.
 * @param      totalsounds  Pointer to an integer where the total number of sounds will be placed.
 *
 * @return     Array of strings with sounds names or NULL.
 */
char** getSoundsName(list_t sounds, int* totalsounds);

#ifdef __cplusplus
}
#endif

#endif // SOUND_H_
