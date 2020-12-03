/*
 * Lucian Tranc
 * 1045249
 * ltranc@uoguelph.ca
 * */
#include "binary.h"
#include "common.h"
#include "name.h"
#include <string.h>

struct name_data * get_name(char * string) {
	
	char buffer[256];
	char * columnString;
	char * dup1;
	char * dup2;
	FILE * fp;
	/*int counter = 0;*/
	int first = 0;
	char * filename;
	int actorCount = 0;
	struct name_basics * nameData;
	struct name_data * returnData;
	
	columnString = malloc(256);
	
	/*filename = malloc(strlen(string) + strlen("/name.basics.small.tsv") + 1);*/
	filename = malloc(strlen(string) + strlen("/name.basics.small.tsv") + 1);

	
	strcpy(filename, string);
	/*strcat(filename, "/name.basics.small.tsv");*/
	strcat(filename, "/name.basics.small.tsv");
		
	fp = fopen(filename, "r+");
	
	while(fgets(buffer, 256, fp)) {
		
		/*printf("buffer: %s\n", buffer);*/
						
		get_column(buffer, columnString, 4);
		
		/*printf("c4=[%s]\n", columnString);*/
		
		if ((strstr(columnString, "actor")) || (strstr(columnString, "actress"))) {
			
			actorCount++;
			
			if (first == 0) {
				nameData = malloc(sizeof(struct name_basics));
				first++;
			}
			else {
				nameData = realloc(nameData, actorCount * sizeof(struct name_basics));
			}
			
			get_column(buffer, columnString, 0);
			dup1 = stringdup(columnString);
			reverseString(dup1);
			nameData[actorCount - 1].nconst = dup1; 
			get_column(buffer, columnString, 1);
			dup2 = stringdup(columnString);
			nameData[actorCount - 1].primaryName = dup2;

		}
		
		/*counter++;
		if (counter == 50)
			break;*/
		
	}
		
	returnData = malloc(sizeof(struct name_data));
	
	returnData->name_basics_ptr = nameData;
	returnData->length = actorCount;
	returnData->nconst_tree = 0;
	returnData->primaryName_tree = 0;

	/*printf("\nname data:\n\n");
	printf("length: %d\n", returnData->length);

	int i = 0;
	for (i = 0; i < returnData->length; i++) {
		printf("%s\n", returnData->name_basics_ptr[i].nconst);
		printf("%s\n", returnData->name_basics_ptr[i].primaryName);
	}*/
	
	fclose(fp);
	free(filename);
		
	return returnData;
	
}


void build_nindex(struct name_data * nameData) {
	
	int i;
		
	for (i = 0; i<nameData->length; i++) {
		
		add_node(&(nameData->primaryName_tree), nameData->name_basics_ptr[i].primaryName, (void *)(&(nameData->name_basics_ptr[i])));
		
	}
	
}

struct name_basics * find_primary_name(struct name_data * nameData, char * string) {
		
	return find_node(nameData->primaryName_tree, string);
		
}

void build_ncindex(struct name_data * nameData) {
	
	int i;
		
	for (i = 0; i<nameData->length; i++) {
		
		add_node(&(nameData->nconst_tree), nameData->name_basics_ptr[i].nconst, (void *)(&(nameData->name_basics_ptr[i])));
		
	}
	
}
struct name_basics * find_nconst(struct name_data * nameData, char * string) {
		
	return find_node(nameData->nconst_tree, string);
		
}
