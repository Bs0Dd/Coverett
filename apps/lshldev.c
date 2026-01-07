#include <stdio.h>
#include <stdlib.h>
#include "coverett.h"

int main(void){
	bus_t stdbus = openBus("/dev/hvc0");
	list_t devlist = getList(stdbus);
	
	int total;
	char** ids = getDevsId(devlist, &total);
	int totalnames;
	char** names;
	puts("HLAPI devices:");
	for (int i = 0; i < total; i++){
		printf("[%d] ID: %s\n", i+1, ids[i]);
		names = getDevNamesByPos(devlist, i, &totalnames);
		printf("    Names: ");
		for (int j = 0; j < totalnames; j++){
			printf("%s", names[j]);
			if (j != totalnames - 1){
				printf(", ");
			}
		}
		free(names);
		putc('\n', stdout);
	}
	closeBus(stdbus);
	return 0;
}
