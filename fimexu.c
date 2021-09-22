#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include "coverett.h"
#include "devices/file_import_export.h"

int main(int argc, char* argv[]){
	if (argc < 2){
		puts("File IMport/EXport Utility");
		puts("Usage: fimexu [-i or -e] <filename>");
		puts("       -i - Import file (you can save it by custom filename).");
		puts("       -e - Export file.");
		return 0;
	}

	BUS stdbus = openBus("/dev/hvc0");
	
	DEVICE dev = findDev(stdbus, "file_import_export");
	if (!dev.exists){
		puts("This program requires a File Import/Export Card.");
		return -1;
	}
	resetTransfer(&dev);
	
	char* lowarg;
	if (strlen(argv[1]) > 1){
		lowarg = strdup(argv[1]);
		lowarg[1] = tolower(lowarg[1]);
	}
	
	if (strcmp(lowarg, "-i") == 0){
		RESULT status = requestImportFile(&dev);
		if (status.type == RESULT_BOOLEAN && !status.retNumber){
			puts("No users present to request file from.");
			return -1;
		}
	
		printf("Waiting for file... ");
	
		FILEINFO fil;
		int gotfile = 0;
		while (!gotfile){
			fil = beginImportFile(&dev);
			if (fil.type == FILEINFO_ERROR){
				if (strcmp(fil.errString, "invalid state") == 0){
					puts("\nFile transfer canceled.");
					return -1;
				}
				printf("\nError while waiting for file: %s.\n", fil.errString);
				return -1;
			}
			else if (fil.type == FILEINFO_OK){
				printf("Ok!\nRemote file: '%s', Size: %d bytes.\n", fil.filename, fil.size);
				gotfile = 1;
			}
		}

		char* fname = argc > 2 ? argv[2] : fil.filename;
		if (access(fname, F_OK) != -1){
			printf("File '%s' exists. [O]verwrite/[U]se another name/[C]ancel? ", fname);
			fflush(stdout);
			char ans = tolower(getc(stdin));
			if (ans == 'o'){
				puts("Overwriting.");
			}
			else if (ans == 'u'){
				int namsiz = 256;
				char* newnam = (char*)malloc(namsiz);
				printf("Enter new name: ");
				fflush(stdout);
				int i = 0;
				getc(stdin);
				char nsym = getc(stdin);
				while (nsym != '\n') {
					newnam[i++] = nsym;
					if (i > 255){
						namsiz+= 256;
						char* newnam = (char*)realloc(newnam, namsiz);
					}
					nsym = getc(stdin);
				}
				newnam[i] = '\0';
				if (strlen(newnam) == 0){
					puts("Canceled (empty filename).");
					return 0;
				}
				fname = newnam;
			}
			else{
				puts("Canceled.");
				return 0;
			}
		}
		FILE* local = fopen(fname, "wb");
		if (local == NULL){
			puts("Error opening file.");
			return -1;
		}

		printf("Importing");
		fflush(stdout);
		while (1){
			RESULT data = readImportFile(&dev);
			if (data.type == RESULT_ERROR){
				fclose(local);
				printf("Error while file importing: %s.\n", data.errString);
				return -1;
			}
			else if (data.type == RESULT_VOID){
				fclose(local);
				puts(" Ok!");
				return 0;
			}
			fwrite(data.retString, 1, data.retNumber, local);
			free(data.retString);
			putc('.', stdout);
			fflush(stdout);
		}
	}
	else if (strcmp(lowarg, "-e") == 0){
		if (argc < 3){
			puts("No filename specified to export.");
			return -1;
		}
		FILE* local = fopen(argv[2], "rb");
		if (local == NULL){
			puts("Error opening file.");
			return -1;
		}
		
		printf("Exporting");
		fflush(stdout);
		beginExportFile(&dev, argv[2]);
		
		char rbuf[800];
		size_t readed = fread(rbuf, 1, 800, local);
		while (readed != 0){
			writeExportFile(&dev, rbuf, readed);
			putc('.', stdout);
			fflush(stdout);
			readed = fread(rbuf, 1, 800, local);
		}
		fclose(local);
		finishExportFile(&dev);
		puts(" Ok!");
		return 0;
		
	}
	else{
		printf("Incorrect parameter - '%s'.\n", argv[1]);
		return -1;
	}
	
	return 0;
}