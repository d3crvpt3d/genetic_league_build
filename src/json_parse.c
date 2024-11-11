#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <cjson/cJSON.h>

#include "include/json_parse.h"

int parseChampStats(char *champ_name, struct Champion *stats){

	struct stat st;
	if(stat("../data/champion.json", &st) != 0){
		return 0;
	}

	char *json_string = malloc(sizeof(char) * st.st_size);

	cJSON *root = cJSON_Parse(json_string);

	cJSON *data = cJSON_GetObjectItem(root, "data");
	cJSON *champ = cJSON_GetObjectItem(root, champ_name);
	cJSON *stats_obj = cJSON_GetObjectItem(root, "stats");

	if (!stats_obj) {
        fprintf(stderr, "Couldn't find Champion stats in JSON\n");
        cJSON_Delete(root);
		free(json_string);
        return -2;
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
	free(json_string);
	return 0;
}

//load all items with tag correlating with function from json file
int getAllItems(struct AllItems *allItems, char **tags){
	
	//TODO	

	return 0;
}

