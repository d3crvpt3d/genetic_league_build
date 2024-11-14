#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <cjson/cJSON.h>

#include "include/json_parse.h"
#include "include/item.h"

cJSON *getJSONObject(char *filename){
	
	//read json item file
	FILE *fptr = fopen(filename, "r");
	if(!fptr){
		fprintf(stderr, "File %s does not exist", filename);
		return 0;
	}

	//get size of json string
	fseek(fptr, 0L, SEEK_END);
	long size = ftell(fptr);
	rewind(fptr);

	//create space for json string
	char *buffer = malloc(size + 1);
	if(!buffer){
		fprintf(stderr, "cant get Memory of size %ldkB", size/1000);
		fclose(fptr);
		return 0;
	}

	long bytes_read = fread(buffer, 1, size, fptr);
	buffer[bytes_read] = '\0';
	fclose(fptr);

	//get JSON Object
	cJSON *obj = cJSON_Parse(buffer);

	free(buffer);
	fclose(fptr);
	return obj;
}

int parseChampStats(char *champ_name, struct Champion *stats){

	//get specific champion as JSON Object
	cJSON *root = getJSONObject("data/champion.json");
	cJSON *data = cJSON_GetObjectItem(root, "data");
	cJSON *champ = cJSON_GetObjectItem(root, champ_name);
	cJSON *stats_obj = cJSON_GetObjectItem(root, "stats");

	if (!stats_obj) {
        fprintf(stderr, "Couldn't find Stats of %s in data/champion.json\n", champ_name);
        cJSON_Delete(root);
        return -3;
    }

	stats->hp = cJSON_GetObjectItem(stats_obj, "hp")->valueint;
    stats->hpperlevel = cJSON_GetObjectItem(stats_obj, "hpperlevel")->valueint;
    stats->mp = cJSON_GetObjectItem(stats_obj, "mp")->valueint;
    stats->mpperlevel = cJSON_GetObjectItem(stats_obj, "mpperlevel")->valueint;
    stats->movespeed = cJSON_GetObjectItem(stats_obj, "movespeed")->valueint;
    stats->armor = cJSON_GetObjectItem(stats_obj, "armor")->valueint;
    stats->armorperlevel = cJSON_GetObjectItem(stats_obj, "armorperlevel")->valuedouble;
    stats->spellblock = cJSON_GetObjectItem(stats_obj, "spellblock")->valueint;
    stats->spellblockperlevel = cJSON_GetObjectItem(stats_obj, "spellblockperlevel")->valuedouble;
    stats->attackrange = cJSON_GetObjectItem(stats_obj, "attackrange")->valueint;
    stats->hpregen = cJSON_GetObjectItem(stats_obj, "hpregen")->valuedouble;
    stats->hpregenperlevel = cJSON_GetObjectItem(stats_obj, "hpregenperlevel")->valuedouble;
    stats->mpregen = cJSON_GetObjectItem(stats_obj, "mpregen")->valuedouble;
    stats->mpregenperlevel = cJSON_GetObjectItem(stats_obj, "mpregenperlevel")->valuedouble;
    stats->crit = cJSON_GetObjectItem(stats_obj, "crit")->valueint;
    stats->critperlevel = cJSON_GetObjectItem(stats_obj, "critperlevel")->valueint;
    stats->attackdamage = cJSON_GetObjectItem(stats_obj, "attackdamage")->valueint;
    stats->attackdamageperlevel = cJSON_GetObjectItem(stats_obj, "attackdamageperlevel")->valuedouble;
    stats->attackspeedperlevel = cJSON_GetObjectItem(stats_obj, "attackspeedperlevel")->valuedouble;
    stats->attackspeed = cJSON_GetObjectItem(stats_obj, "attackspeed")->valuedouble;

	cJSON_Delete(root);
	return 0;
}

//load all items with tag correlating with function from json file
int mallocAllItems(struct AllItems *allItems, char **tags){
	
	cJSON *obj = getJSONObject("data/item.json");

	//TODO	

	cJSON_Delete(obj);
	return 0;
}

