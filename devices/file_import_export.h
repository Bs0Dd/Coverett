#ifndef FILE_IMPORT_EXPORT_H_
#define FILE_IMPORT_EXPORT_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "../coverett-private.h"

/**
 * @brief      Starts exporting the file.
 *
 * @param[in]  device    Pointer to device proxy (DEVICE structure).
 * @param[in]  filename  String with the name of the exporting file.
 *
 * @return     RESULT structure with the type of RESULT_VOID or RESULT_ERROR.
 */
RESULT beginExportFile(DEVICE* device, char* filename);

/**
 * @brief      Sends the data of the exporting file.
 *
 * @param[in]  device      Pointer to device proxy (DEVICE structure).
 * @param[in]  data        Array of the data bytes.
 * @param[in]  sizeofdata  Size of the data array.
 *
 * @return     RESULT structure with the type of RESULT_VOID or RESULT_ERROR.
 */
RESULT writeExportFile(DEVICE* device, char* data, int sizeofdata);

/**
 * @brief      Finishes exporting the file.
 *
 * @param[in]  device  Pointer to device proxy (DEVICE structure).
 *
 * @return     RESULT structure with the type of RESULT_VOID or RESULT_ERROR.
 */
RESULT finishExportFile(DEVICE* device);

/**
 * @brief      Requests the file for importing.
 *
 * @param[in]  device  Pointer to device proxy (DEVICE structure).
 *
 * @return     RESULT structure with the type of RESULT_BOOLEAN or RESULT_ERROR.
 */
RESULT requestImportFile(DEVICE* device);

/**
 * @brief      Starts importing the file.
 *
 * @param[in]  device  Pointer to device proxy (DEVICE structure).
 *
 * @return     FILEINFO structure with the type of FILEINFO_OK or FILEINFO_NOFILE or FILEINFO_ERROR.
 */
FILEINFO beginImportFile(DEVICE* device);

/**
 * @brief      Gets the data of the importing file.
 *
 * @param[in]  device  Pointer to device proxy (DEVICE structure).
 *
 * @return     RESULT structure with the type of RESULT_BYTES or RESULT_VOID or RESULT_ERROR.
 */
RESULT readImportFile(DEVICE* device);

/**
 * @brief      Resets card and file transfer.
 *
 * @param[in]  device  Pointer to device proxy (DEVICE structure).
 *
 * @return     RESULT structure with the type of RESULT_VOID or RESULT_ERROR.
 */
RESULT resetTransfer(DEVICE* device);

#ifdef __cplusplus
}
#endif

#endif // FILE_IMPORT_EXPORT_H_
