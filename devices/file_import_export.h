#ifndef FILE_IMPORT_EXPORT_H_
#define FILE_IMPORT_EXPORT_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "../coverett-private.h"

RESULT beginExportFile(DEVICE* device, char* filename);

RESULT writeExportFile(DEVICE* device, char* data, int sizeofdata);

RESULT finishExportFile(DEVICE* device);

RESULT requestImportFile(DEVICE* device);

FILEINFO beginImportFile(DEVICE* device);

RESULT readImportFile(DEVICE* device);

RESULT resetTransfer(DEVICE* device);

#ifdef __cplusplus
}
#endif

#endif // FILE_IMPORT_EXPORT_H_
