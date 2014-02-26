/**
 * This file has no copyright assigned and is placed in the Public Domain
 * No warranty is given
 */
#ifndef INC_STR
#define INC_STR

#define STR_CHECK_NULL_SRC
#define STR_CHECK_NULL_DST

char* str_cpy(char**, const char*);
char* str_cat(char**, const char*);
int str_printf(char**, const char*, ...);
void str_free(char**);

#endif
