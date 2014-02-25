/**
 * This file has no copyright assigned and is placed in the Public Domain
 * No warranty is given
 */
#ifndef INC_STR
#define INC_STR

char* str_cpy(char**, const char*);
char* str_cat(char**, const char*);
int str_printf(char**, const char*, ...);
void str_free(char**);

#endif
