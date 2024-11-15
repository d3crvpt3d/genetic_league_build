#pragma once

#include "build.h"
#include "json_parse.h"

//CHANGE VERSION!
#define DDRAGON_0 "/data/en_US/champion.json"
#define VERSION 14.22.1
#define DDRAGON_1_ITEMS "/data/en_US/item.json"
#define DDRAGON_1_CHAMPION "/data/en_US/champion.json"

float evalFunction(struct Build *, struct Champion *);
