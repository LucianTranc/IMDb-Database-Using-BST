/*
 * Lucian Tranc
 * 1045249
 * ltranc@uoguelph.ca
 * */
#include <stdio.h>
#include <stdlib.h>

struct title_basics {
	char *tconst;
	char *primaryTitle;
};

struct title_data {
	struct title_basics *title_basics_ptr;
	int length;
	struct tree *tconst_tree;
	struct tree *primaryTitle_tree;
	
};

struct title_data * get_title(char * string);
void build_tindex(struct title_data * titleData);
struct title_basics * find_primary_title(struct title_data * titleData, char * string);
void build_tcindex(struct title_data * titleData);
struct title_basics * find_tconst(struct title_data * titleData, char * string);
