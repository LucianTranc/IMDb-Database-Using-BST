/*
 * Lucian Tranc
 * 1045249
 * ltranc@uoguelph.ca
 * */
#include <stdio.h>
#include <stdlib.h>

struct tree{
	
	void * dataPtr;
	char * keyPtr;
	struct tree *children[2];
	
};

void add_node (struct tree ** root, char * key, void * data);
void * find_node (struct tree * root, char * string);
struct tree * find_node_list (struct tree * root, char * string);
