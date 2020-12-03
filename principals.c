/*
 * Lucian Tranc
 * 1045249
 * ltranc@uoguelph.ca
 * */
#include "principals.h"
#include "binary.h"
#include "common.h"

struct principals_data * get_principals(char * string) {
	
	char buffer[256];
	char * columnString;
	char * dup1;
	char * dup2;
	char * dup3;
	FILE * fp;
	/*int counter = 0;*/
	int first = 0;
	char * filename;
	int principalsCount = 0;
	struct principals_basics * principalsData;
	struct principals_data * returnData;
	
	columnString = malloc(256);
	
	/*filename = malloc(strlen(string) + strlen("/title.principals.small.tsv") + 1);*/
	filename = malloc(strlen(string) + strlen("/title.principals.small.tsv") + 1);

	
	strcpy(filename, string);
	/*strcat(filename, "/title.principals.small.tsv");*/
	strcat(filename, "/title.principals.small.tsv");
		
	fp = fopen(filename, "r+");
	
	while(fgets(buffer, 256, fp)) {
		
		/*printf("buffer: %s\n", buffer);*/
						
		get_column(buffer, columnString, 3);
		
		/*printf("c4=[%s]\n", columnString);*/
		
		if ((strstr(columnString, "actor")) || (strstr(columnString, "actress"))) {
			
			principalsCount++;
			
			if (first == 0) {
				principalsData = malloc(sizeof(struct principals_basics));
				first++;
			}
			else {
				principalsData = realloc(principalsData, principalsCount * sizeof(struct principals_basics));
			}
			
			get_column(buffer, columnString, 0);
			dup1 = stringdup(columnString);
			reverseString(dup1);
			principalsData[principalsCount - 1].tconst = dup1; 
			
			get_column(buffer, columnString, 2);
			dup2 = stringdup(columnString);
			reverseString(dup2);
			principalsData[principalsCount - 1].nconst = dup2;
			
			
			
			get_column(buffer, columnString, 5);
			dup3 = stringdup(columnString);
			principalsData[principalsCount - 1].characters = dup3;
			
		}
		
		/*counter++;
		if (counter == 50)
			break;*/
		
	}
		
	returnData = malloc(sizeof(struct principals_data));
	
	returnData->principals_basics_ptr = principalsData;
	returnData->length = principalsCount;
	returnData->tconst_tree = 0;
	returnData->nconst_tree = 0;

	/*printf("\nprincipals data:\n\n");
	printf("length: %d\n", returnData->length);

	int i = 0;
	for (i = 0; i < returnData->length; i++) {
		printf("%s\n", returnData->principals_basics_ptr[i].nconst);
		printf("%s\n", returnData->principals_basics_ptr[i].tconst);
		printf("%s\n", returnData->principals_basics_ptr[i].characters);
	}
	*/
	
	fclose(fp);
	free(filename);
		
	return returnData;
	
	
}


void build_ptindex(struct principals_data * principalsData) {
	
	int i;
		
	for (i = 0; i<principalsData->length; i++) {
		
		/*printf("ADDING NODE ptindex:\n");
		printf("charcters: %s\n", (&(principalsData->principals_basics_ptr[i]))->characters);
		printf("nconst: %s\n", (&(principalsData->principals_basics_ptr[i]))->nconst);
		printf("tconst: %s\n", (&(principalsData->principals_basics_ptr[i]))->tconst);
		printf("%s\n", principalsData->principals_basics_ptr[i].tconst);*/
		add_node(&(principalsData->tconst_tree), principalsData->principals_basics_ptr[i].tconst, (void *)(&(principalsData->principals_basics_ptr[i])));
		
	}
	
}

struct principals_basics * find_ptconst(struct principals_data * principalsData, char * string) {
		
	return find_node(principalsData->tconst_tree, string);
		
}

struct tree * find_ptconst_list(struct principals_data * principalsData, char * string) {
		
	struct tree * returnTree;
	
	returnTree = find_node_list(principalsData->tconst_tree, string);
				
	return returnTree;
		
}


void build_pnindex(struct principals_data * principalsData) {
	
	int i;

	
		
	for (i = 0; i<principalsData->length; i++) {
		/*printf("ADDING NODE pnindex:\n");
		printf("charcters: %s\n", (&(principalsData->principals_basics_ptr[i]))->characters);
		printf("nconst: %s\n", (&(principalsData->principals_basics_ptr[i]))->nconst);
		printf("tconst: %s\n", (&(principalsData->principals_basics_ptr[i]))->tconst);
		printf("%s\n", principalsData->principals_basics_ptr[i].tconst);*/
		add_node(&(principalsData->nconst_tree), principalsData->principals_basics_ptr[i].nconst, (void *)(&(principalsData->principals_basics_ptr[i])));
		
	}
	
}

struct principals_basics * find_pnconst(struct principals_data * principalsData, char * string) {
		
	return find_node(principalsData->nconst_tree, string);
		
}

struct tree * find_pnconst_list(struct principals_data * principalsData, char * string) {
		
	struct tree * returnTree;
	
	returnTree = find_node_list(principalsData->nconst_tree, string);
				
	return returnTree;
		
}

