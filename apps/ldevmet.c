#include <stdio.h>
#include "coverett.h"

int main(int argc, char* argv[]){
	if (argc < 2){
		puts("List DEVice METhods");
		puts("Usage: ldevmet <devname>");
		return 0;
	}

	bus_t stdbus = openBus("/dev/hvc0");
	device_t dev = findDev(stdbus, argv[1]);
	if (!dev.exists){
		fprintf(stderr, "Device \"%s\" is not found.\n", argv[1]);
		closeBus(stdbus);
		return -1;
	}

	list_t meth = getMethods(&dev);
	if (meth.type == CO_ERROR){
		fputs("Failed to get methods list.\n", stderr);
		closeBus(stdbus);
		return -1;
	}
	closeBus(stdbus);

	int msiz;
	method_t* mes = parseMethods(meth, &msiz);
	deleteList(&meth);

	if (mes == NULL){
		fputs("Failed to parse methods list.\n", stderr);
		return -1;
	}
	
	printf("Methods for device \"%s\":\n", argv[1]);
	for (int i = 0; i < msiz; i++){
		printf("    - %s(",mes[i].name);
		int narg = 1;
		for (int j = 0; j < mes[i].paramNum; j++){
			if (mes[i].parameters[j].name){
				printf("%s: ", mes[i].parameters[j].name);
			} else{
				printf("arg%d: ", narg++);
			}
			printf("%s", mes[i].parameters[j].type);
			if (j+1 < mes[i].paramNum) printf(", ");
		}
		printf("): %s\n", mes[i].returnType);
		if (mes[i].description != NULL){
			printf("        %s", mes[i].description);
			if (mes[i].description[strlen(mes[i].description)-1] != '\n') printf("\n");
		}
		narg = 1;
		for (int j = 0; j < mes[i].paramNum; j++){
			if (mes[i].parameters[j].description != NULL){
				if (mes[i].parameters[j].name){
					printf("        '%s' - ", mes[i].parameters[j].name);
				} else{
					printf("        'arg%d' - ", narg++);
				}
				printf("%s\n", mes[i].parameters[j].description);
			}
		}
		printf("\n");
	}
	
	deleteParsedMethods(mes, msiz);
	
	return 0;
}
