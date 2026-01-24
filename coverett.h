#ifndef COVERETT_H_
#define COVERETT_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include "cJSON/cJSON.h"

#define CO_NULL_DEVICE (device_t){0, NULL, NULL,NULL}
    
typedef enum TYPES {
	CO_ERROR = -1, //Error status
	CO_BOOLEAN, CO_LIST, CO_VOID, // Answer types for result_t
	CO_NUMBER, CO_STRING, CO_BYTES, // Answer types for result_t / also data types for uniInvoke
	CO_DEVICES, CO_METHODS, CO_SOUNDS, CO_DELETED, // Types for list_t
	CO_OK, CO_NOFILE, CO_EMPTY // Types for fileinfo_t / stackinfo_t
} cotypes_t;


typedef FILE* bus_t;

typedef struct{
	cotypes_t type;
	cJSON* body;
	char* errString;
} list_t;

typedef struct{
	char* name;
	char* description;
	char* type;
} param_t;

typedef struct{
	char* name;
	char* returnType;
	char* description;
	char* returnValueDescription;
	int paramNum;
	param_t* parameters;
} method_t;

typedef struct{
	int exists;
	const char* devType;
	const char* devId;
	bus_t busPtr;
} device_t;

typedef struct{
	cotypes_t type;
	double retNumber;
	char* retString;
	cJSON* retList;
	char* errString;
} result_t;

typedef struct{
	cotypes_t type;
	char* filename;
	size_t size;
	char* errString;
} fileinfo_t;

typedef struct{
	cotypes_t type;
	char* itemId;
	int itemCount;
	char* errString;
} stackinfo_t;


/**
 * @brief      Create a new descriptor for bus.
 *
 * @param[in]  path  Path to the bus character special file (default "/dev/hvc0").
 *
 * @return     bus_t descriptor or NULL.
 */
bus_t openBus(char* path);

/**
 * @brief      Close bus descriptor.
 *
 * @param[in]  bus  Bus descriptor.
 *
 * @return     Closing status.
 */
int closeBus(bus_t bus);

/**
 * @brief      Get devices list.
 *
 * @param[in]  bus  Bus descriptor.
 *
 * @return     List of type CO_DEVICES or CO_ERROR.
 */
list_t getList(bus_t bus);

/**
 * @brief      Delete list (free memory).
 *
 * @param[in]  list  List for deleting. After function will be CO_DELETED.
 */
void deleteList(list_t* list);

/**
 * @brief      Get devices ID by list.
 *
 * @param[in]  list          List of the type CO_DEVICES.
 * @param      totaldevices  Pointer to an integer where the total number of devices will be placed.
 *
 * @return     Array of strings with devices ID or NULL.
 */
char** getDevsId(list_t list, int* totaldevices);

/**
 * @brief      Get device names by position in list.
 *
 * @param[in]  list        List of the type CO_DEVICES.
 * @param[in]  position    Device position in list (zero-based).
 * @param      totalnames  Pointer to an integer where the total number of names will be placed.
 *
 * @return     Array of strings with device names or NULL.
 */
char** getDevNamesByPos(list_t list, int position, int* totalnames);

/**
 * @brief      Get device names by ID.
 *
 * @param[in]  list        List of the type CO_DEVICES.
 * @param[in]  id          Device ID.
 * @param      totalnames  Pointer to an integer where the total number of names will be placed.
 *
 * @return     Array of strings with device names or NULL.
 */
char** getDevNamesById(list_t list, char* id, int* totalnames);

/**
 * @brief      Get device ID by name.
 *
 * @param[in]  list  List of type CO_DEVICES.
 * @param[in]  name  Device name.
 *
 * @return     String with device ID or NULL.
 */
char* getDevIdByName(list_t list, char* name);

/**
 * @brief      Get device proxy by ID.
 *
 * @param[in]  bus  Bus descriptor.
 * @param[in]  id   Device ID.
 *
 * @return     device_t structure.
 */
device_t proxyDev(bus_t bus, char* id);

/**
 * @brief      Get device proxy by name.
 *
 * @param[in]  bus  Bus descriptor.
 * @param[in]  id   Device ID.
 *
 * @return     device_t structure.
 */
device_t findDev(bus_t bus, char* name);

/**
 * @brief      Get methods list.
 *
 * @param[in]  device  Pointer to device proxy (device_t structure).
 *
 * @return     List of the type CO_METHODS or CO_ERROR.
 */
list_t getMethods(device_t* device);

/**
 * @brief      Parse methods list.
 *
 * @param[in]  list   List of type CO_METHODS.
 * @param[in]  meths  Pointer to an integer where the total number of methods will be placed.
 *
 * @return     Array of method_t structures or NULL.
 */
method_t* parseMethods(list_t list, int* meths);

/**
 * @brief      Delete array of method_t structures (free memory).
 *
 * @param[in]  methods  Array of method_t structures.
 * @param[in]  meths    Pointer to an integer where the total number of methods will be placed.
 */
void deleteParsedMethods(method_t* methods, int meths);

/**
 * @brief      Unversal invoker for methods.
 *
 * @param[in]  device   Pointer to device proxy (device_t structure).
 * @param[in]  method   Method name.
 * @param[in]  numvals  Number (double) parameters.
 * @param[in]  strvals  String parameters.
 * @param[in]  total    Total number of parameters.
 * @param[in]  order    Parameter insertion order (e.g. {CO_NUMBER, CO_STRING, CO_STRING}).
 *
 * @return     result_t structure with the type of CO_BOOLEAN, CO_LIST, CO_VOID, CO_NUMBER, CO_STRING or CO_BYTES.
 */
result_t uniInvoke(device_t* dev, char* method, double* numvals, 
                          char** strvals, int total, cotypes_t* order);

#ifdef __cplusplus
}
#endif

#endif // COVERETT_H_
