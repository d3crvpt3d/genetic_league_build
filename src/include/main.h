#pragma once

#include "build.h"

#define GENERATION_LENGTH 256

//CHANGE VERSION!
#define DDRAGON_0 "/data/en_US/champion.json"
#define VERSION 14.22.1
#define DDRAGON_1_ITEMS "/data/en_US/item.json"
#define DDRAGON_1_CHAMPION "/data/en_US/champion.json"

//each Generation consists of 256 builds, where [0,1] are the best of last Generation aka new parents
struct Generation{
	struct Build builds[GENERATION_LENGTH];
};

float evalFunction(struct Build *);
