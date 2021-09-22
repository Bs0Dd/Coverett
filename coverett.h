#ifndef COVERETT_H_
#define COVERETT_H_

#include "coverett-private.h"


BUS openBus(char* path);

int closeBus(BUS bus);

LIST getList(BUS bus);

void deleteList(LIST* list);

char** getDevsId(LIST list, int* totaldevices);

char** getDevNamesByPos(LIST list, int position, int* totalnames);

char** getDevNamesById(LIST list, char* id, int* totalnames);

char* getDevIdByName(LIST list, char* name);

DEVICE proxyDev(BUS bus, char* id);

DEVICE findDev(BUS bus, char* name);

LIST getMethods(DEVICE* device);

#endif // COVERETT_H_
