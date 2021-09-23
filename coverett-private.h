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

typedef FILE* BUS;

typedef struct{
	int type;
	cJSON* body;
	char* errString;
} LIST;

typedef struct{
	int exists;
	const char* devType;
	const char* devId;
	BUS busPtr;
} DEVICE;

typedef struct{
	int type;
	int retNumber;
	char* retString;
	cJSON* retList;
	char* errString;
} RESULT;

typedef struct{
	int type;
	char* filename;
	size_t size;
	char* errString;
} FILEINFO;

typedef struct{
	int type;
	char* itemId;
	int itemCount;
	char* errString;
} STACKINFO;


void writeData(BUS bus, char* body);

char* readData(BUS bus);

cJSON* request(BUS bus, char* body, char* exptype, int* status);

DEVICE proxyDevByList(BUS bus, LIST list, char* id);

int existsStatus(DEVICE* dev);

RESULT universalInvoker(DEVICE* dev, char* methodname, int* numvals, char** strvals, int nofpar, int* packord);

#ifdef __cplusplus
}
#endif

#endif // COVERETT_PRIVATE_H_
