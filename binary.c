/*
 * Lucian Tranc
 * 1045249
 * ltranc@uoguelph.ca
 * */
#include "common.h"
#include "binary.h"


void add_node (struct tree ** root, char * key, void * data) {
	
	if (*root) {
		
		
		if (strcmp(key, (*root)->keyPtr) < 0) {
			
			/*printf("0 branch taken, %s < %s\n", key, (*root)->keyPtr);*/
			add_node( &((*root)->children[0]), key, data);
			
		}
		else {
			
			/*printf("1 branch taken, %s > %s\n", key, (*root)->keyPtr);*/
			add_node( &((*root)->children[1]), key, data);
			
		}
		
	}
	else {
		
		(*root) = malloc(sizeof(struct tree));
		(*root)->keyPtr = key;
		(*root)->dataPtr = data;
		(*root)->children[0] = NULL;
		(*root)->children[1] = NULL;
		
	}
	
}

void * find_node (struct tree * root, char * string) {
	
	if (!root) {
		
		return NULL;
		
	}
	
	if ((strcmp(root->keyPtr, string)) != 0) {
		
		if (strcmp(string, root->keyPtr) < 0) {
			
			/*printf("0 branch taken, %s < %s\n", key, (*root)->keyPtr);*/
			return find_node( root->children[0], string);
			
		}
		else {
			
			/*printf("1 branch taken, %s > %s\n", key, (*root)->keyPtr);*/
			return find_node( root->children[1], string);
			
		}
		
	}
	else {

		return root->dataPtr;

	}
	
	
	return NULL;
	
}

struct tree * find_node_list (struct tree * root, char * string) {
	
	if (!root) {
		
		return NULL;
		
	}
	
	if ((strcmp(root->keyPtr, string)) != 0) {
		
		if (strcmp(string, root->keyPtr) < 0) {
			
			/*printf("0 branch taken, %s < %s\n", key, (*root)->keyPtr);*/
			return find_node_list( root->children[0], string);
			
		}
		else {
			
			/*printf("1 branch taken, %s > %s\n", key, (*root)->keyPtr);*/
			return find_node_list( root->children[1], string);
			
		}
		
	}
	else {

		return root;

	}
	
	
	return NULL;
	
}

