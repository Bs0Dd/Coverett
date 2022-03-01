#ifndef FILE_IMPORT_EXPORT_H_
#define FILE_IMPORT_EXPORT_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "../coverett.h"

/**
 * @brief      Starts exporting the file.
 *
 * @param[in]  device    Pointer to device proxy (device_t structure).
 * @param[in]  filename  String with the name of the exporting file.
 *
 * @return     result_t structure with the type of CO_VOID or CO_ERROR.
 */
result_t beginExportFile(device_t* device, char* filename);

/**
 * @brief      Sends the data of the exporting file.
 *
 * @param[in]  device      Pointer to device proxy (device_t structure).
 * @param[in]  data        Array of the data bytes.
 * @param[in]  sizeofdata  Size of the data array.
 *
 * @return     result_t structure with the type of CO_VOID or CO_ERROR.
 */
result_t writeExportFile(device_t* device, char* data, int sizeofdata);

/**
 * @brief      Finishes exporting the file.
 *
 * @param[in]  device  Pointer to device proxy (device_t structure).
 *
 * @return     result_t structure with the type of CO_VOID or CO_ERROR.
 */
result_t finishExportFile(device_t* device);

/**
 * @brief      Requests the file for importing.
 *
 * @param[in]  device  Pointer to device proxy (device_t structure).
 *
 * @return     result_t structure with the type of CO_BOOLEAN or CO_ERROR.
 */
result_t requestImportFile(device_t* device);

/**
 * @brief      Starts importing the file.
 *
 * @param[in]  device  Pointer to device proxy (device_t structure).
 *
 * @return     fileinfo_t structure with the type of CO_OK or CO_NOFILE or CO_ERROR.
 */
fileinfo_t beginImportFile(device_t* device);

/**
 * @brief      Gets the data of the importing file.
 *
 * @param[in]  device  Pointer to device proxy (device_t structure).
 *
 * @return     result_t structure with the type of CO_BYTES or CO_VOID or CO_ERROR.
 */
result_t readImportFile(device_t* device);

/**
 * @brief      Resets card and file transfer.
 *
 * @param[in]  device  Pointer to device proxy (device_t structure).
 *
 * @return     result_t structure with the type of CO_VOID or CO_ERROR.
 */
result_t resetTransfer(device_t* device);

#ifdef __cplusplus
}
#endif

#endif // FILE_IMPORT_EXPORT_H_
