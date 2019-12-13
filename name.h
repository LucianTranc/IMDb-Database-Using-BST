/*
 * Lucian Tranc
 * 1045249
 * ltranc@uoguelph.ca
 * */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct name_basics {
	char *nconst;
	char *primaryName;
};

struct name_data {
	struct name_basics *name_basics_ptr;
	int length;
	struct tree *nconst_tree;
	struct tree *primaryName_tree;
	
};

struct name_data * get_name(char * string);
void build_nindex(struct name_data * nameData);
struct name_basics * find_primary_name(struct name_data * nameData, char * string);
void build_ncindex(struct name_data * nameData);
struct name_basics * find_nconst(struct name_data * nameData, char * string);

