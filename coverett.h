#ifndef COVERETT_H_
#define COVERETT_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "coverett-private.h"


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
 * @return     List of type LIST_LIST or LIST_ERROR.
 */
list_t getList(bus_t bus);

/**
 * @brief      Delete list (free memory).
 *
 * @param[in]  list  List for deleting. After function will be LIST_DELETED.
 */
void deleteList(list_t* list);

/**
 * @brief      Get devices ID by list.
 *
 * @param[in]  list          List of the type LIST_LIST.
 * @param      totaldevices  Pointer to an integer where the total number of devices will be placed.
 *
 * @return     Array of strings with devices ID or NULL.
 */
char** getDevsId(list_t list, int* totaldevices);

/**
 * @brief      Get device names by position in list.
 *
 * @param[in]  list        List of the type LIST_LIST.
 * @param[in]  position    Device position in list (zero-based).
 * @param      totalnames  Pointer to an integer where the total number of names will be placed.
 *
 * @return     Array of strings with device names or NULL.
 */
char** getDevNamesByPos(list_t list, int position, int* totalnames);

/**
 * @brief      Get device names by ID.
 *
 * @param[in]  list        List of the type LIST_LIST.
 * @param[in]  id          Device ID.
 * @param      totalnames  Pointer to an integer where the total number of names will be placed.
 *
 * @return     Array of strings with device names or NULL.
 */
char** getDevNamesById(list_t list, char* id, int* totalnames);

/**
 * @brief      Get device ID by name.
 *
 * @param[in]  list  List of type LIST_LIST.
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
 * @return     List of the type LIST_METHODS or LIST_ERROR.
 */
list_t getMethods(device_t* device);

#ifdef __cplusplus
}
#endif

#endif // COVERETT_H_
