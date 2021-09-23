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
 * @return     BUS descriptor or NULL.
 */
BUS openBus(char* path);

/**
 * @brief      Close bus descriptor.
 *
 * @param[in]  bus  Bus descriptor.
 *
 * @return     Closing status.
 */
int closeBus(BUS bus);

/**
 * @brief      Get devices list.
 *
 * @param[in]  bus  Bus descriptor.
 *
 * @return     List of type LIST_LIST or LIST_ERROR.
 */
LIST getList(BUS bus);

/**
 * @brief      Delete list (free memory).
 *
 * @param[in]  list  List for deleting. After function will be LIST_DELETED.
 */
void deleteList(LIST* list);

/**
 * @brief      Get devices ID by list.
 *
 * @param[in]  list          List of the type LIST_LIST.
 * @param      totaldevices  Pointer to an integer where the total number of devices will be placed.
 *
 * @return     Array of strings with devices ID or NULL.
 */
char** getDevsId(LIST list, int* totaldevices);

/**
 * @brief      Get device names by position in list.
 *
 * @param[in]  list        List of the type LIST_LIST.
 * @param[in]  position    Device position in list (zero-based).
 * @param      totalnames  Pointer to an integer where the total number of names will be placed.
 *
 * @return     Array of strings with device names or NULL.
 */
char** getDevNamesByPos(LIST list, int position, int* totalnames);

/**
 * @brief      Get device names by ID.
 *
 * @param[in]  list        List of the type LIST_LIST.
 * @param[in]  id          Device ID.
 * @param      totalnames  Pointer to an integer where the total number of names will be placed.
 *
 * @return     Array of strings with device names or NULL.
 */
char** getDevNamesById(LIST list, char* id, int* totalnames);

/**
 * @brief      Get device ID by name.
 *
 * @param[in]  list  List of type LIST_LIST.
 * @param[in]  name  Device name.
 *
 * @return     String with device ID or NULL.
 */
char* getDevIdByName(LIST list, char* name);

/**
 * @brief      Get device proxy by ID.
 *
 * @param[in]  bus  Bus descriptor.
 * @param[in]  id   Device ID.
 *
 * @return     DEVICE structure.
 */
DEVICE proxyDev(BUS bus, char* id);

/**
 * @brief      Get device proxy by ID.
 *
 * @param[in]  bus  Bus descriptor.
 * @param[in]  id   Device ID.
 *
 * @return     DEVICE structure.
 */
DEVICE findDev(BUS bus, char* name);

/**
 * @brief      Get devices list.
 *
 * @param[in]  device  Pointer to device proxy (DEVICE structure).
 *
 * @return     List of the type LIST_METHODS or LIST_ERROR.
 */
LIST getMethods(DEVICE* device);

#ifdef __cplusplus
}
#endif

#endif // COVERETT_H_
