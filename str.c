#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "str.h"

#define STR_ALLOC_INC  32
#define STR_ROUNDUP(A) (((A)/STR_ALLOC_INC+1)*STR_ALLOC_INC)

typedef struct {
    size_t size;
    char  str;
} str_t;

char* str_alloc(size_t len)
{
    size_t newlen = STR_ROUNDUP(sizeof(str_t)+len+1);
    str_t* newstr = malloc(newlen);
#ifdef STR_CHECK_NULL_ALLOCS
    if (newstr==NULL)
        return NULL;
#endif
    newstr->size = newlen;
    return &(newstr->str);
}

char* str_realloc(char** s, size_t newlen)
/* FIXME: does not check s nor *s for NULL */
{
    str_t* str = (str_t*)(*s - offsetof(str_t, str));
    size_t len = str->size;
    str_t* newstr;
    char*  news;
    if (newlen<=len)
        return *s;
    news = str_alloc(newlen);
#ifdef STR_CHECK_NULL_ALLOCS
    if (news == NULL)
        return NULL;
#endif
    newstr = (str_t*)(*s - offsetof(str_t, str));
    newstr->size = newlen;
    memmove(news, *s, len + 1);
    return news;
}

void str_free(char** strptr)
{
    char* s = *strptr;
    str_t *str = (str_t*)(s - offsetof(str_t, str));
    free(str);
    (*strptr) = NULL;
}

char* str_cpy(char** dst, const char* src)
{
    size_t srcsize;
    char *newdst;
#ifdef STR_CHECK_NULL_SRC
    if (src==NULL)
        newdst = NULL;
    else 
#endif
    {
        srcsize = strlen(src);
        if (*dst==NULL)
            newdst = str_alloc(srcsize);
        else
            newdst = str_realloc(dst, srcsize);
#ifdef STR_CHECK_NULL_ALLOCS
        if (newdst==NULL)
            return NULL;
#endif
        memmove(newdst, src, srcsize+1);
    }
    (*dst) = newdst;
    return newdst;
}

char* str_cat(char** dst, const char* src)
{
    size_t dstsize, srcsize, newdstsize;
    char *olddst = *dst;
    char *newdst;
#ifdef STR_CHECK_NULL_SRC
    if (src==NULL)
        return olddst;
#endif
#ifdef STR_CHECK_NULL_DST
    if (dst==NULL || olddst == NULL)
        return olddst;
#endif
    dstsize = strlen(olddst);
    srcsize = strlen(src);
    newdstsize = dstsize + srcsize;
    if (newdstsize==0)
        return olddst;
    newdst = str_realloc(dst, newdstsize);
#ifdef STR_CHECK_NULL_ALLOCS
    if (newdst==NULL)
        return NULL;
#endif
    memmove(newdst+dstsize, src, srcsize+1); 
    (*dst) = newdst;
    return newdst;
}


int str_printf(char** dst, const char* fmt, ...)
{
    return 0;
}


