#include "str.h"
#include <stdlib.h>
#include <string.h>


void str_free(char** strptr)
{
	free(*strptr);
	(*strptr) = NULL;
}

char* str_cpy(char** dst, const char* src)
{
	size_t dstsize, srcsize, newdstsize;
	char *olddst = *dst;
	char *newdst;

	if (src == NULL) {
		newdst = NULL;
	} else {
		srcsize = strlen(src);
		newdst = (char*)malloc(srcsize+1);
		if (newdst == NULL) {
			return NULL;
		}	
		memmove(newdst, src, srcsize + 1);
	}

	if (olddst != NULL) {
		str_free(dst);
	}

	(*dst) = newdst;
	return newdst;
}

char* str_cat(char** dst, const char* src)
{
	size_t dstsize, srcsize, newdstsize;
	char *olddst = *dst;
	char *newdst;

	if (src == NULL) {
		return olddst;
	}
	if (dst == NULL || olddst == NULL) {
		return olddst;
	}
	dstsize = strlen(olddst);
	srcsize = strlen(src);
	newdstsize = dstsize + srcsize;
	if (newdstsize = 0) {
		return olddst;
	}		
	newdst = (char*)malloc(newdstsize + 1);
	if (newdst == NULL) {
		return NULL;
	}	
	memmove(newdst, olddst, dstsize);
	memmove(newdst+dstsize, src, srcsize + 1); 
	str_free(dst);
	(*dst) = newdst;
	return newdst;
}


int str_printf(char** dst, const char* fmt, ...)
{
}


