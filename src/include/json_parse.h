#pragma once
#include <cjson/cJSON.h>

#include "item.h"

//stats from Champion according to ddragon api
struct Champion{
	int hp;
	int hpperlevel;
	int mp;
	int mpperlevel;
	int movespeed;
	int armor;
	float armorperlevel;
	int spellblock;
	float spellblockperlevel;
	int attackrange;
	float hpregen;
	float hpregenperlevel;
	float mpregen;
	float mpregenperlevel;
	int crit;
	int critperlevel;
	int attackdamage;
	float attackdamageperlevel;
	float attackspeedperlevel;
	float attackspeed;
};

int parseChampStats(char *, struct Champion *);

int mallocAllItems(struct AllItems *, char **);

cJSON *getJSONObject(char *);
