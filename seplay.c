#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include "coverett.h"
#include "devices/sound.h"

int main(int argc, char* argv[]){
	if (argc < 2){
		puts("Sound Effects PLAYer");
		puts("Usage: seplay [-f] <effect name or search query>");
		puts("       -f - Get effects list by search query");
		return 0;
	}

	bus_t stdbus = openBus("/dev/hvc0");
	
	device_t dev = findDev(stdbus, "sound");
	if (!dev.exists){
		puts("This program requires a Sound Card.");
		return -1;
	}
	
	char* lowarg;
	if (strlen(argv[1]) > 1){
		lowarg = strdup(argv[1]);
		lowarg[1] = tolower(lowarg[1]);
	}
	
	if (strcmp(lowarg, "-f") == 0){
		if (argc < 3){
			puts("No search query specified");
			return -1;
		}
		list_t sounds = findSound(&dev, argv[2]);
		if (sounds.type == LIST_ERROR){
			printf("Error: %s\n", sounds.errString);
			return -1;
		}
		int total;
		char** names = getSoundsName(sounds, &total);
		puts("Found effects:");
		for (int i = 0; i < total; i++){
			puts(names[i]);
		}
	}
	else{
		result_t stat = playSound(&dev, argv[1]);
		if (stat.type == RESULT_ERROR){
			printf("Error: %s\n", stat.errString);
			return -1;
		}
	}
	
	return 0;
}
