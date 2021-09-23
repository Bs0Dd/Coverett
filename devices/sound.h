#ifndef SOUND_H_
#define SOUND_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "../coverett-private.h"

RESULT playSound(DEVICE* device, char* name);

LIST findSound(DEVICE* device, char* name);

char** getSoundsName(LIST sounds, int* totalsounds);

#ifdef __cplusplus
}
#endif

#endif // SOUND_H_
