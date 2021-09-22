#ifndef SOUND_H_
#define SOUND_H_

#include "../coverett-private.h"

RESULT playSound(DEVICE* device, char* name);

LIST findSound(DEVICE* device, char* name);

char** getSoundsName(LIST sounds, int* totalsounds);

#endif // SOUND_H_
