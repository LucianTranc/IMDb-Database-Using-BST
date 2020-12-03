/*
 * Lucian Tranc
 * 1045249
 * ltranc@uoguelph.ca
 * */
#include "common.h"

void get_column(char * string, char * returnString, int columnNumber) {
	
	int length;
	int i;
	int tabCounter = 0;
	int prevTabIndex = 0;
	int tabIndex = 0;
	int firstTabFound = 0;
	/*printf("string, cn %d: %s", columnNumber, string);*/
	columnNumber++;
	length = strlen(string);
	
	for (i = 0; i<length; i++) {
		
		if (columnNumber == 1) {
			
			prevTabIndex = 0;
			firstTabFound = 1;
			
		}
		
		if ((string[i] == '\t') || (string[i] == '\n')) {
			tabCounter++;
		}
		
		if ((tabCounter == (columnNumber-1)) && (firstTabFound == 0)) {
			
			prevTabIndex = i;
			prevTabIndex++;
			firstTabFound = 1;
			
		}
		
		if (tabCounter == columnNumber) {
			
			tabIndex = i;
			break;
			
		}
		
	}

	
	for (i = 0; i<=(tabIndex - prevTabIndex); i++) {
		
		if (i == (tabIndex - prevTabIndex)) {
			returnString[i] = '\0';
			break;
		}

		returnString[i] = string[prevTabIndex + i];
	}
	
	/*printf("return string: %s\n\n", returnString);*/
	
}

char *stringdup(const char * src) { /*https://stackoverflow.com/questions/252782/strdup-what-does-it-do-in-c*/
	
	char *dst = malloc(strlen (src) + 1);
    if (dst == NULL) return NULL;
    strcpy(dst, src);
    return dst;
	
}

void reverseString(char * str) {
	
	int end = strlen(str) - 1;
	int start = 0;
	char temp;
	
	while (start<end) {
		
		temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
	
}
