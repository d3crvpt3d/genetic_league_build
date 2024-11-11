#pragma once

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

//where the actual items are stored
struct AllItems{
	struct Item items[ITEM_SIZE];
};

int getAllItems(struct AllItems *, char **);
