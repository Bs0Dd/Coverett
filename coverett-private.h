#ifndef COVERETT_PRIVATE_H_
#define COVERETT_PRIVATE_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "coverett.h"


void writeData(bus_t bus, char* body);

char* readData(bus_t bus);

cJSON* request(bus_t bus, char* body, char* exptype, int* status);

device_t proxyDevByList(bus_t bus, list_t list, char* id);

int existsStatus(device_t* dev);

#ifdef __cplusplus
}
#endif

#endif // COVERETT_PRIVATE_H_
