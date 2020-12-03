/*
 * Lucian Tranc
 * 1045249
 * ltranc@uoguelph.ca
 * */
#include <stdio.h>
#include <stdlib.h>
#include "binary.h"
#include "common.h"
#include "name.h"
#include "principals.h"
#include "title.h"
#include "ctype.h"


int main(int argc, char *argv[]) {
	

	struct title_data * titleData;
	struct name_data * nameData;
	struct principals_data * principalsData;
	struct title_basics * foundNodeTitle;
	struct name_basics * foundNodeName;
	struct principals_basics * foundNodePrincipals;
	struct tree * actorTree;
	char * target;
	char * command;
	char * mode;
	int i ,j;
	int spaceCounter = 0;
	target = malloc(256);
	mode = malloc(256);
	command = malloc(256);
	titleData = malloc(sizeof(struct title_data));
	nameData = malloc(sizeof(struct name_data));
	principalsData = malloc(sizeof(struct principals_data));
	
	

	if (argc != 2) {
		
		fprintf(stderr, "Usage: %s directory\n", argv[0]);
		return -1;
		
	}
	printf("Command format:\n>\"mode\" \"target\"\n");
	printf("Example:\n");
	printf("> name Chris Hemsworth\n");
	printf("To enter a movie use \"title\" as the mode instead of \"name\"\n");
	printf("> ");
	fgets(command, 256, stdin);	
	spaceCounter = 0;
	
	for(i = 0; i<strlen(command); i++) {
		
		if (isspace(command[i]) == 0) {
			break;
		}
		else {
			spaceCounter++;
		}
		
	}
	
	command += spaceCounter;
	
	for(i = (strlen(command)-1); i>=0; i--) {
		
		
		if (isspace(command[i]) == 0) {
			break;
		}
		else {
			command[i] = '\0';
		}
		
	}
	spaceCounter = 0;
	command[strlen(command)] = '\0';
	
	for(i = 0; i<strlen(command); i++) {
		
		if (isspace(command[i]) == 0) {
			spaceCounter++;
		}
		else{
			break;
		}
		
	}
	
	strncat(mode, command, i);

	for(j = i; j<strlen(command); j++) {
		
		if (isspace(command[j]) == 0) {
			
			break;
			
		}
		else{
			spaceCounter++;
		}
		
	}
	command += spaceCounter;
	strncat(target, command, 256);

	if (strcmp(mode, "title") == 0) {
		
		titleData = get_title(argv[1]);
		
		printf("creating tcindex...\n");
		build_tcindex(titleData);	
		printf("creating tindex...\n");
		build_tindex(titleData);
	
		nameData = get_name(argv[1]);
		
		printf("creating ncindex...\n");
		build_ncindex(nameData);
		printf("creating nindex...\n");
		build_nindex(nameData);
	
		principalsData = get_principals(argv[1]);
		
		printf("creating pnindex...\n");
		build_pnindex(principalsData);
		printf("creating ptindex...\n");
		build_ptindex(principalsData);
		
		foundNodeTitle = find_primary_title( titleData, target );
		
		actorTree = find_ptconst_list(principalsData, foundNodeTitle->tconst);

		printf("Actors that played in target:\n");

		while (actorTree) {
			
			foundNodePrincipals = (struct principals_basics *)(actorTree->dataPtr);

			/*printf("principal data:\n");
			printf("tconst: %s\n", foundNodePrincipals->tconst);
			printf("nconst: %s\n", foundNodePrincipals->nconst);
			printf("characters: %s\n", foundNodePrincipals->characters);*/
						
			foundNodeName = find_nconst(nameData, foundNodePrincipals->nconst);
		
			if (foundNodeName) {
		
				if (strcmp(foundNodeTitle->tconst, actorTree->keyPtr) == 0)
				{
					printf("\n%s: ", foundNodeName->primaryName);
					printf("%s\n\n", foundNodePrincipals->characters);
				}
				

				if (strcmp(foundNodeTitle->tconst, actorTree->keyPtr) < 0) {
			
					actorTree = actorTree->children[0];
				
				}
				else {
				
					actorTree = actorTree->children[1];
				
				}

			}
		
		}
	
	}
	else if (strcmp(mode,"name") == 0) {
		
		titleData = get_title(argv[1]);
		
		printf("creating tcindex...\n");
		build_tcindex(titleData);
		printf("creating tindex...\n");
		build_tindex(titleData);
	
		nameData = get_name(argv[1]);
		
		printf("creating ncindex...\n");
		build_ncindex(nameData);
		printf("creating nindex...\n");
		build_nindex(nameData);
	
		principalsData = get_principals(argv[1]);
		
		printf("creating pnindex...\n");
		build_pnindex(principalsData);
		printf("creating ptindex...\n");
		build_ptindex(principalsData);
		
		foundNodeName = find_primary_name(nameData, target);

		/*printf("\n\nFound Node: %s, %s\n\n", foundNodeName->primaryName, foundNodeName->nconst);*/
		
		actorTree = find_pnconst_list(principalsData, foundNodeName->nconst);
		
		printf("Movies and roles of %s:\n", target);

		while (actorTree) {
			
			foundNodePrincipals = (struct principals_basics *)(actorTree->dataPtr);
						
			/*printf("principal data:\n");
			printf("tconst: %s\n", foundNodePrincipals->tconst);
			printf("nconst: %s\n", foundNodePrincipals->nconst);
			printf("characters: %s\n", foundNodePrincipals->characters);*/
			foundNodeTitle = find_tconst(titleData, foundNodePrincipals->tconst);
		
			if (foundNodeTitle) {

				if (strcmp(foundNodeName->nconst, actorTree->keyPtr) == 0) {

					printf("\n%s: ", foundNodeTitle->primaryTitle);
					printf("%s\n\n", foundNodePrincipals->characters);					

				}

				if (strcmp(foundNodeName->nconst, actorTree->keyPtr) < 0) {

					actorTree = actorTree->children[0];
			
				}
				else {
				
					actorTree = actorTree->children[1];
				
				}

			}
		
		}
		
	}
	return 0;
}
