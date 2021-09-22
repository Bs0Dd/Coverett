#include "../coverett-private.h"
#include "../coverett.h"

const RESULT FIEINC = {RESULT_ERROR, 0, NULL, NULL, "Incorrect device type"};

int isFIECard(DEVICE* dev){
	if (strcmp(dev->devType, "oc2:file_import_export_card") != 0){
		return 0;
	}
	return 1;
}



RESULT beginExportFile(DEVICE* device, char* filename){
	if (!isFIECard(device)) return FIEINC;
	char* strvals[] = {filename};
	int packord[] = {1};
	return universalInvoker(device, "beginExportFile", NULL, strvals, 1, packord);
}

RESULT writeExportFile(DEVICE* device, char* data, int sizeofdata){
	if (!isFIECard(device)) return FIEINC;
	char* strvals[] = {data};
	int packord[] = {2, sizeofdata};
	return universalInvoker(device, "writeExportFile", NULL, strvals, 1, packord);
}

RESULT finishExportFile(DEVICE* device){
	if (!isFIECard(device)) return FIEINC;
	return universalInvoker(device, "finishExportFile", NULL, NULL, 0, NULL);
}

RESULT requestImportFile(DEVICE* device){
	if (!isFIECard(device)) return FIEINC;
	return universalInvoker(device, "requestImportFile", NULL, NULL, 0, NULL);
}

FILEINFO beginImportFile(DEVICE* device){
	if (!isFIECard(device)) return (FILEINFO){FILEINFO_ERROR, NULL, 0, "Incorrect device type"};
	RESULT ans = universalInvoker(device, "beginImportFile", NULL, NULL, 0, NULL);
	if (ans.type == RESULT_LIST){
		char* filename = strdup(cJSON_GetObjectItemCaseSensitive(ans.retList, "name")->valuestring);
		size_t size = cJSON_GetObjectItemCaseSensitive(ans.retList, "size")->valueint;
		cJSON_Delete(ans.retList);
		return (FILEINFO){FILEINFO_OK, filename, size, NULL};
	}
	else if (ans.type == RESULT_VOID){
		return (FILEINFO){FILEINFO_NOFILE, NULL, 0, NULL};
	}
	else{
		return (FILEINFO){FILEINFO_ERROR, NULL, 0, (ans.errString != NULL) ? ans.errString : "Unknown error"};
	}
}

RESULT readImportFile(DEVICE* device){
	if (!isFIECard(device)) return FIEINC;
	return universalInvoker(device, "readImportFile", NULL, NULL, 0, NULL);
}

RESULT resetTransfer(DEVICE* device){
	if (!isFIECard(device)) return FIEINC;
	return universalInvoker(device, "reset", NULL, NULL, 0, NULL);
}
