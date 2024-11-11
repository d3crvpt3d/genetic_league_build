#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/build.h"
#include "include/item.h"
#include "include/main.h"
#include "include/json_parse.h"


//return random new item
struct Item *getRandomItem(struct AllItems *allItems){
	return &allItems->items[rand()%ITEM_SIZE];
}

//do new geneeration from best 2 of last generation
int buildNewGeneration(struct Build *parents, struct Generation *generation, struct AllItems *allItems){
	
	//parents are in next gen
	generation->builds[0] = parents[0];
	generation->builds[1] = parents[1];

	//generate random byte and use last 5 as bitmask for DNA, and first 3 as mutate
	for(int i=2; i < GENERATION_LENGTH; i++){

		char random = (char) rand();
 		
		generation->builds[i].items[0] = generation->builds[(random >> 0) & 1].items[0];
		generation->builds[i].items[1] = generation->builds[(random >> 1) & 1].items[1];
		generation->builds[i].items[2] = generation->builds[(random >> 2) & 1].items[2];
		generation->builds[i].items[3] = generation->builds[(random >> 3) & 1].items[3];
		generation->builds[i].items[4] = generation->builds[(random >> 4) & 1].items[4];
		
		//if all first 3 bit == 0 mutate
		if((random>>5) == 0){
			generation->builds[i].items[random%5] = getRandomItem(allItems);
		}
	}

	return 0;
}

float evalFunction(struct Build *b){

	//TODO
	
	return 0;
}

void createScores(struct Generation *gen){
	
	for(int i = 0; i < GENERATION_LENGTH; i++){
		gen->builds[i].score = evalFunction(&gen->builds[i]);
	}

}

int main(int argc, char **argv) {

	if(strcmp(argv[1], "help")){
		printf("genetic_build <Champion> [<Tag1, Tag2, ...>]");
		return 0;
	}

	//loadChampion
	struct Champion champ;
	parseChampStats(argv[1], &champ);

	//load all items into allItems Buffer
	struct AllItems allItems;

	getAllItems(&allItems, argv);

	//create starting parents
	struct Build parents[2];
	struct Build b1 = {&allItems.items[0%ITEM_SIZE], &allItems.items[1%ITEM_SIZE], &allItems.items[2%ITEM_SIZE], &allItems.items[3%ITEM_SIZE], &allItems.items[4%ITEM_SIZE]};
	struct Build b2 = {&allItems.items[5%ITEM_SIZE], &allItems.items[6%ITEM_SIZE], &allItems.items[7%ITEM_SIZE], &allItems.items[8%ITEM_SIZE], &allItems.items[9%ITEM_SIZE]};
	parents[0] = b1;//interesting that assignmend isnt available in C
	parents[1] = b2;

	struct Generation gen;

	int same_score = 0;
	float last_score = 0;

	//if 64x same score print best of generation
	while(same_score < 64){
		buildNewGeneration(parents, &gen, &allItems);
		
		createScores(&gen);
		
		if(gen.builds[0].score == last_score){
			same_score++;
		}else{
			last_score = gen.builds[0].score;
		}
	}

	printf("Best Build: %s, %s, %s, %s, %s\n",
			gen.builds[0].items[0]->name,
			gen.builds[0].items[1]->name,
			gen.builds[0].items[2]->name,
			gen.builds[0].items[3]->name,
			gen.builds[0].items[4]->name);

    return 0;
}
