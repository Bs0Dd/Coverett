#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include "coverett.h"
#include "devices/sound.h"

int main(int argc, char* argv[]){
	if (argc < 2){
		puts("Sound Effects PLAYer");
		puts("Usage: seplay [-f] <effect name or search query> [volume, pitch]");
		puts("       -f - Get effects list by search query");
        puts("       volume - [0, 1], pitch - [0.5, 2]");
		return 0;
	}

	bus_t stdbus = openBus("/dev/hvc0");
	
	device_t dev = findDev(stdbus, "sound");
	if (!dev.exists){
		fputs("This program requires a Sound Card.\n", stderr);
		return -1;
	}
	
	char* lowarg;
	if (strlen(argv[1]) > 1){
		lowarg = strdup(argv[1]);
		lowarg[1] = tolower(lowarg[1]);
	}
	
	if (strcmp(lowarg, "-f") == 0){
		if (argc < 3){
			fputs("No search query specified\n", stderr);
			return -1;
		}
		list_t sounds = findSound(&dev, argv[2]);
		if (sounds.type == CO_ERROR){
			fprintf(stderr, "Error: %s\n", sounds.errString);
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
		double volume = argc > 2 ? atof(argv[2]) : NAN;
		double pitch = argc > 3 ? atof(argv[3]) : NAN;
		result_t stat = playSound(&dev, argv[1], volume, pitch);
		if (stat.type == CO_ERROR){
			fprintf(stderr, "Error: %s\n", stat.errString);
			return -1;
		}
	}
	
	return 0;
}
