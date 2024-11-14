#pragma once

#define ITEM_SIZE 20

struct Item{
	int id;
	char name[64];
	float critChance;
	int attackDamage;
	float attackSpeed;
	float critDamage;
	int lethality;
	float armorPen;
	int abilityHaste;
	int abilityPower;
	int flatMagicPen;
	float percMagicPen;
};

//where the actual items are stored
struct AllItems{
	int size;
	struct Item *items;
};
