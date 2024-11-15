#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

cJSON *filter_by_map11(cJSON *data) {
    cJSON *filtered_data = cJSON_CreateObject(); // Create a new object for filtered data
    cJSON *item = NULL;

    // Iterate through the objects in "data"
    cJSON_ArrayForEach(item, data) {
        if (cJSON_IsObject(item)) {
            cJSON *maps = cJSON_GetObjectItem(item, "maps");
            if (maps != NULL && cJSON_IsObject(maps)) {
                cJSON *map11 = cJSON_GetObjectItem(maps, "11");
                if (map11 != NULL && cJSON_IsBool(map11) && cJSON_IsTrue(map11)) {
                    // Add the item to the filtered_data object
                    cJSON_AddItemToObject(
                        filtered_data,
                        item->string, // Copy the key
                        cJSON_Duplicate(item, 1)); // Deep copy the value
                }
            }
        }
    }

    return filtered_data; // Return the filtered object
}

// Function to check if any tag matches the filter tags
int has_matching_tags(cJSON *tags, char *filter_tags[], int filter_count) {
    cJSON *tag = NULL;
    cJSON_ArrayForEach(tag, tags) {
        if (cJSON_IsString(tag)) {
            for (int i = 0; i < filter_count; i++) {
                if (strcmp(tag->valuestring, filter_tags[i]) == 0) {
                    return 1; // Found a matching tag
                }
            }
        }
    }
    return 0; // No matching tag found
}

// Function to filter by tags
cJSON *filter_by_tags(cJSON *filtered_data, char *filter_tags[], int filter_count) {
    cJSON *result = cJSON_CreateObject(); // To store items that match the tags
    cJSON *item = NULL;

    // Iterate through the filtered items
    cJSON_ArrayForEach(item, filtered_data) {
        cJSON *tags = cJSON_GetObjectItem(item, "tags");
        if (tags != NULL && cJSON_IsArray(tags) && has_matching_tags(tags, filter_tags, filter_count)) {
            // Add matching item to the result
            cJSON_AddItemToObject(result, item->string, cJSON_Duplicate(item, 1));
        }
    }

    return result; // Return the new filtered object
}

struct Item *parse_stats_to_item_array(cJSON *filtered_data, int *item_count) {
    int count = cJSON_GetArraySize(filtered_data); // Count the items
    *item_count = count;
    struct Item *items = malloc(sizeof(struct Item) * count); // Allocate memory for the items
    if (!items) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    int index = 0;
    cJSON *item = NULL;
    cJSON_ArrayForEach(item, filtered_data) {
        if (!cJSON_IsObject(item)) continue;

        // Parse the "name"
        cJSON *name = cJSON_GetObjectItem(item, "name");
        if (cJSON_IsString(name)) {
            strncpy(items[index].name, name->valuestring, sizeof(items[index].name) - 1);
            items[index].name[sizeof(items[index].name) - 1] = '\0'; // Ensure null termination
        } else {
            items[index].name[0] = '\0'; // Default to empty string
        }

        // Parse the "stats"
        cJSON *stats = cJSON_GetObjectItem(item, "stats");
        if (cJSON_IsObject(stats)) {
            cJSON *attackDamage = cJSON_GetObjectItem(stats, "FlatPhysicalDamageMod");
            cJSON *attackSpeed = cJSON_GetObjectItem(stats, "FlatAttackSpeedMod");
            cJSON *critChance = cJSON_GetObjectItem(stats, "FlatCritChanceMod");
            cJSON *critChance = cJSON_GetObjectItem(stats, "FlatCritChanceMod");
            
			items[index].critChance = c;
            items[index].attackDamage = cJSON_IsNumber(AttackDamage) ? flatDamage->valuedouble : 0.0f;
			items[index].attackSpeed = cJSON_IsNumber(AttackSpeed) ? flatDamage->valuedouble : 0.0f;
			items[index].critDamage = 0.0f;
			items[index].lethality = 0;
			items[index].armorPen = 0.0f;
			items[index].abilityHaste = 0;
            items[index].abilityPower = 0;
            items[index].flatMagicPen = 0;
            items[index].percMagicPen = 0.0f;
        } else {
			items[index].critChance = 0.0f;
			items[index].attackDamage = 0;
			items[index].attackSpeed = 0.0f;
			items[index].critDamage = 0.0f;
			items[index].lethality = 0;
			items[index].armorPen = 0.0f;
			items[index].abilityHaste = 0;
            items[index].abilityPower = 0;
            items[index].flatMagicPen = 0;
            items[index].percMagicPen = 0.0f;
        }

        index++;
    }

    return items;
}

//load all items with tag correlating with function from json file
int mallocAllItems(struct AllItems *allItems, char **tags, int tag_count){
	
	cJSON *obj = getJSONObject("data/item.json");
	cJSON *data = cJSON_GetObjectItem(obj, "data");

	cJSON *filtered_data = filter_by_map11(data);
	cJSON *filtered_by_tags = filter_by_tags(filtered_data, tags, tag_count);

	//parse items to struct and update allItems.size
	allItems->items = parse_stats_to_item_array(filtered_by_tags, &allItems->size);


	cJSON_Delete(obj);
	cJSON_Delete(data);
	return 0;
}

