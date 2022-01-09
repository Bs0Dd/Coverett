#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/stat.h>
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

	bus_t stdbus = openBus("/dev/hvc0");
	
	device_t dev = findDev(stdbus, "file_import_export");
	if (!dev.exists){
		fputs("This program requires a File Import/Export Card.\n", stderr);
		return -1;
	}
	resetTransfer(&dev);
	
	char* lowarg;
	if (strlen(argv[1]) > 1){
		lowarg = strdup(argv[1]);
		lowarg[1] = tolower(lowarg[1]);
	}
	
	if (strcmp(lowarg, "-i") == 0){
		result_t status = requestImportFile(&dev);
		if (status.type == RESULT_BOOLEAN && !status.retNumber){
			fputs("No users present to request file from.\n", stderr);
			return -1;
		}
	
		puts("Waiting for file...");
	
		fileinfo_t fil;
		int gotfile = 0;
		while (!gotfile){
			fil = beginImportFile(&dev);
			if (fil.type == FILEINFO_ERROR){
				if (strcmp(fil.errString, "invalid state") == 0){
					fputs("File transfer canceled.\n", stderr);
					return -1;
				}
				fprintf(stderr, "Error while waiting for file: %s.\n", fil.errString);
				return -1;
			}
			else if (fil.type == FILEINFO_OK){
				printf("Remote file: '%s', Size: %ld bytes.\n", fil.filename, fil.size);
				gotfile = 1;
			}
		}
		
		char* fname = argc > 2 ? argv[2] : fil.filename;
		
		struct stat st;
		stat(fname, &st);
		
		if (argc > 2 && S_ISDIR(st.st_mode)){
			size_t arlen = strlen(argv[2]);
			fname = (char*)malloc(arlen+strlen(fil.filename)+2);
			strcpy(fname, argv[2]);
			if (fname[arlen-1] != '/'){
				fname[arlen] = '/';
				fname[arlen+1] = 0;
			}
			strcat(fname, fil.filename);
		}
		
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
			perror("Error opening file");
			return -1;
		}

		fflush(stdout);
		size_t recv = 0;
		result_t data = readImportFile(&dev);
		if (data.type != RESULT_VOID){
			while (data.type != RESULT_VOID){
				if (data.type == RESULT_ERROR){
					fclose(local);
					putc('\n',stdout);
					fprintf(stderr, "Error while file importing: %s.\n", data.errString);
					return -1;
				}
				size_t wrt = fwrite(data.retString, 1, data.retNumber, local);
				if (wrt != data.retNumber){
					fclose(local);
					putc('\n',stdout);
					perror("Error while file importing");
					return -1;
				}
				free(data.retString);
				recv += data.retNumber;
				printf("\rImporting... %.2f%%", (double)(recv * 100) / fil.size);
				fflush(stdout);
				data = readImportFile(&dev);
			}
		}
		else{
			printf("Importing... 100.00%%");
		}
		
		fclose(local);
	}
	else if (strcmp(lowarg, "-e") == 0){
		if (argc < 3){
			fputs("No filename specified to export.\n", stderr);
			return -1;
		}
		FILE* local = fopen(argv[2], "rb");
		if (local == NULL){
			perror("Error opening file");
			return -1;
		}
		struct stat st;
		fstat(fileno(local), &st);
		
		if (S_ISDIR(st.st_mode)){
			fputs("Error: this is a directory.\n", stderr);
			return -1;
		}
		
		
		fflush(stdout);
		beginExportFile(&dev, argv[2]);
		
		char rbuf[800];
		size_t readed = fread(rbuf, 1, 800, local);
		size_t sent = 0;
		if (readed != 0){
			while (readed != 0){
				writeExportFile(&dev, rbuf, readed);
				sent += readed;
				printf("\rExporting... %.2f%%", (double)(sent * 100) / st.st_size);
				fflush(stdout);
				readed = fread(rbuf, 1, 800, local);
			}
		}
		else{
			printf("Exporting... 100.00%%");
		}
		
		fclose(local);
		finishExportFile(&dev);
	}
	else{
		fprintf(stderr, "Incorrect parameter - '%s'.\n", argv[1]);
		return -1;
	}
	puts("\nDone!");
	
	return 0;
}
