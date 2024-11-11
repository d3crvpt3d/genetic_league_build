#pragma once

#define ITEM_SIZE 20

struct Item{
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
