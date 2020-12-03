/*
 * Lucian Tranc
 * 1045249
 * ltranc@uoguelph.ca
 * */
#include "title.h"
#include "binary.h"
#include "common.h"

struct title_data * get_title(char * string) {
	
	char buffer[256];
	char * columnString;
	char * dup1;
	char * dup2;
	FILE * fp;
	/*int counter = 0;*/
	int first = 0;
	char * filename;
	int movieCount = 0;
	struct title_basics * titleData;
	struct title_data * returnData;
	int isAdult = 0;
	
	columnString = malloc(256);
	
	/*filename = malloc(strlen(string) + strlen("/title.basics.small.tsv") + 1);*/
	filename = malloc(strlen(string) + strlen("/title.basics.small.tsv") + 1);
	
	strcpy(filename, string);
	/*strcat(filename, "/title.basics.small.tsv");*/
	strcat(filename, "/title.basics.small.tsv");
		
	fp = fopen(filename, "r+");
	
	while(fgets(buffer, 256, fp)) {
		/*printf("buffer: %s\n", buffer);*/
		
		get_column(buffer, columnString, 4);
		if (strcmp(columnString, "0")) {
			isAdult = 1;
		}
		else {
			isAdult = 0;
		}
		get_column(buffer, columnString, 1);
		
		if ((strstr(columnString, "movie")) && (isAdult == 0)) {
			
			movieCount++;
			
			if (first == 0) {
				titleData = malloc(sizeof(struct title_basics));
				first++;
			}
			else {
				titleData = realloc(titleData, movieCount * sizeof(struct title_basics));
			}
			
			get_column(buffer, columnString, 0);
			dup1 = stringdup(columnString);
			reverseString(dup1);
			titleData[movieCount - 1].tconst = dup1; 
			get_column(buffer, columnString, 2);
			dup2 = stringdup(columnString);
			titleData[movieCount - 1].primaryTitle = dup2;

		}
		
		/*counter++;
		if (counter == 50)
			break;*/
		
	}
		
	returnData = malloc(sizeof(struct title_data));
	
	returnData->title_basics_ptr = titleData;
	returnData->length = movieCount;
	returnData->tconst_tree = 0;
	returnData->primaryTitle_tree = 0;
	
	fclose(fp);
	free(filename);

	/*printf("\ntitle data:\n\n");
	printf("length: %d\n", returnData->length);

	int i = 0;
	for (i = 0; i < returnData->length; i++) {
		printf("%s\n", returnData->title_basics_ptr[i].tconst);
		printf("%s\n", returnData->title_basics_ptr[i].primaryTitle);
	}*/
		
	return returnData;
	
	
}

void build_tindex(struct title_data * titleData) {
	
	int i;
		
	for (i = 0; i<titleData->length; i++) {
		
		add_node(&(titleData->primaryTitle_tree), titleData->title_basics_ptr[i].primaryTitle, (void *)(&(titleData->title_basics_ptr[i])));
		
	}
	
}

struct title_basics * find_primary_title(struct title_data * titleData, char * string) {
		
	return find_node(titleData->primaryTitle_tree, string);
		
}

void build_tcindex(struct title_data * titleData) {
	
	int i;
		
	for (i = 0; i<titleData->length; i++) {
		
		add_node(&(titleData->tconst_tree), titleData->title_basics_ptr[i].tconst, (void *)(&(titleData->title_basics_ptr[i])));
		
	}
	
}

struct title_basics * find_tconst(struct title_data * titleData, char * string) {
		
	/*printf("find tconst\n");
	printf("string: %s\n", string);
	printf("dataptr=%s\n", (char*)titleData->tconst_tree->dataPtr);
	printf("keyptr=%s\n", titleData->tconst_tree->keyPtr);*/

	return (struct title_basics*)find_node(titleData->tconst_tree, string);
		
}
