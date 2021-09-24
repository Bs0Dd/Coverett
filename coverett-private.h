#ifndef COVERETT_PRIVATE_H_
#define COVERETT_PRIVATE_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON/cJSON.h"


#define RESULT_BOOLEAN 66
#define RESULT_LIST 73
#define RESULT_NUMBER 78
#define RESULT_STRING 83
#define RESULT_VOID 86
#define RESULT_BYTES 89
#define RESULT_ERROR -1

#define LIST_LIST 76
#define LIST_METHODS 77
#define LIST_SOUNDS 79
#define LIST_ERROR -1
#define LIST_DELETED 68

#define FILEINFO_ERROR -1
#define FILEINFO_OK 0
#define FILEINFO_NOFILE 1

#define STACKINFO_ERROR -1
#define STACKINFO_OK 0
#define STACKINFO_EMPTY 1

typedef FILE* bus_t;

typedef struct{
	int type;
	cJSON* body;
	char* errString;
} list_t;

typedef struct{
	int exists;
	const char* devType;
	const char* devId;
	bus_t busPtr;
} device_t;

typedef struct{
	int type;
	int retNumber;
	char* retString;
	cJSON* retList;
	char* errString;
} result_t;

typedef struct{
	int type;
	char* filename;
	size_t size;
	char* errString;
} fileinfo_t;

typedef struct{
	int type;
	char* itemId;
	int itemCount;
	char* errString;
} stackinfo_t;


void writeData(bus_t bus, char* body);

char* readData(bus_t bus);

cJSON* request(bus_t bus, char* body, char* exptype, int* status);

device_t proxyDevByList(bus_t bus, list_t list, char* id);

int existsStatus(device_t* dev);

result_t universalInvoker(device_t* dev, char* methodname, int* numvals, char** strvals, int nofpar, int* packord);

#ifdef __cplusplus
}
#endif

#endif // COVERETT_PRIVATE_H_
