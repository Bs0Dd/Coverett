#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "coverett.h"
#include "devices/redstone.h"

int main(int argc, char* argv[]){
	if (argc < 2){
		puts("Usage: redstone <side name> [<value>]");
		return 0;
	}
	BUS stdbus = openBus("/dev/hvc0");
	
	DEVICE dev = findDev(stdbus, "redstone");
	if (!dev.exists){
		puts("This program requires a Redstone Interface Card or Redstone Interface.");
		return -1;
	}
	
	char* side = argv[1];
	int i = 0;
	while (side[i] != 0){
		side[i] = tolower(side[i]);
		i++;
	}
	
	RESULT in = getRedstoneInput(&dev, side);
	if (in.type == RESULT_ERROR){
		printf("%s.\n", in.errString);
		return -1;
	}
	
	
	if (argc > 2){
		int strength;
		char* yesval[] = {"true", "on", "yes"};
		for (int i = 0; i < 3; i++){
			if (strcmp(yesval[i], argv[2]) == 0){
				strength = 15;
				break;
			}
			if (i == 2){
				strength = atoi(argv[2]);
			}
		}
		
		setRedstoneOutput(&dev, side, strength);
	}
	
	
	RESULT out= getRedstoneOutput(&dev, side);
	printf("Input: %d\nOutput: %d\n", in.retNumber, out.retNumber);
	closeBus(stdbus);
	return 0;
}
