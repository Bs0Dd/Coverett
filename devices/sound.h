#ifndef SOUND_H_
#define SOUND_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "../coverett-private.h"

/**
 * @brief      Attempts to play the specified sound.
 *
 * @param[in]  device  Pointer to device proxy (DEVICE structure).
 * @param[in]  name    Name of the sound to play.
 *
 * @return     RESULT structure with the type of RESULT_VOID or RESULT_ERROR.
 */
RESULT playSound(DEVICE* device, char* name);

/**
 * @brief      Finds the sounds by the string.
 *
 * @param[in]  device  Pointer to device proxy (DEVICE structure).
 * @param[in]  string  String to search.
 *
 * @return     LIST structure with the type of LIST_SOUNDS or LIST_ERROR.
 */
LIST findSound(DEVICE* device, char* string);

/**
 * @brief      Gets the sounds names from list.
 *
 * @param[in]  list         List of the type LIST_SOUNDS.
 * @param      totalsounds  Pointer to an integer where the total number of sounds will be placed.
 *
 * @return     Array of strings with sounds names or NULL.
 */
char** getSoundsName(LIST sounds, int* totalsounds);

#ifdef __cplusplus
}
#endif

#endif // SOUND_H_
