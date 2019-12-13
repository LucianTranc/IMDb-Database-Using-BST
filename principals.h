/*
 * Lucian Tranc
 * 1045249
 * ltranc@uoguelph.ca
 * */
#include <stdio.h>
#include <stdlib.h>

struct principals_basics {
	char *tconst;
	char *nconst;
	char *characters;
};

struct principals_data {
	struct principals_basics *principals_basics_ptr;
	int length;
	struct tree *tconst_tree;
	struct tree *nconst_tree;
	
};

struct principals_data * get_principals(char * string);
struct principals_basics * find_ptconst(struct principals_data * principalsData, char * string);
void build_ptindex(struct principals_data * principalsData);
void build_pnindex(struct principals_data * principalsData);
struct principals_basics * find_pnconst(struct principals_data * principalsData, char * string);
struct tree * find_pnconst_list(struct principals_data * principalsData, char * string);
struct tree * find_ptconst_list(struct principals_data * principalsData, char * string);
