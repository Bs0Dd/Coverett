#include "../coverett-private.h"
#include "../coverett.h"

const result_t FIEINC = {RESULT_ERROR, 0, NULL, NULL, "Incorrect device type"};

int isFIECard(device_t* dev){
	if (strcmp(dev->devType, "oc2:file_import_export_card") != 0){
		return 0;
	}
	return 1;
}



result_t beginExportFile(device_t* device, char* filename){
	if (!isFIECard(device)) return FIEINC;
	char* strvals[] = {filename};
	int packord[] = {1};
	return universalInvoker(device, "beginExportFile", NULL, strvals, 1, packord);
}

result_t writeExportFile(device_t* device, char* data, int sizeofdata){
	if (!isFIECard(device)) return FIEINC;
	char* strvals[] = {data};
	int packord[] = {2, sizeofdata};
	return universalInvoker(device, "writeExportFile", NULL, strvals, 1, packord);
}

result_t finishExportFile(device_t* device){
	if (!isFIECard(device)) return FIEINC;
	return universalInvoker(device, "finishExportFile", NULL, NULL, 0, NULL);
}

result_t requestImportFile(device_t* device){
	if (!isFIECard(device)) return FIEINC;
	return universalInvoker(device, "requestImportFile", NULL, NULL, 0, NULL);
}

fileinfo_t beginImportFile(device_t* device){
	if (!isFIECard(device)) return (fileinfo_t){FILEINFO_ERROR, NULL, 0, "Incorrect device type"};
	result_t ans = universalInvoker(device, "beginImportFile", NULL, NULL, 0, NULL);
	if (ans.type == RESULT_LIST){
		char* filename = strdup(cJSON_GetObjectItemCaseSensitive(ans.retList, "name")->valuestring);
		size_t size = cJSON_GetObjectItemCaseSensitive(ans.retList, "size")->valueint;
		cJSON_Delete(ans.retList);
		return (fileinfo_t){FILEINFO_OK, filename, size, NULL};
	}
	else if (ans.type == RESULT_VOID){
		return (fileinfo_t){FILEINFO_NOFILE, NULL, 0, NULL};
	}
	else{
		return (fileinfo_t){FILEINFO_ERROR, NULL, 0, (ans.errString != NULL) ? ans.errString : "Unknown error"};
	}
}

result_t readImportFile(device_t* device){
	if (!isFIECard(device)) return FIEINC;
	return universalInvoker(device, "readImportFile", NULL, NULL, 0, NULL);
}

result_t resetTransfer(device_t* device){
	if (!isFIECard(device)) return FIEINC;
	return universalInvoker(device, "reset", NULL, NULL, 0, NULL);
}
