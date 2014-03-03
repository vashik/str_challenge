#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "str.h"

#define STR_ALLOC_INC  64 /* allocate by blocks of this size */ 
#define STR_CONTAINER(s) ((str_t*)((*(s)) - offsetof(str_t, str)))

typedef struct {
    size_t len;
    size_t maxlen;
    char  str;
} str_t;

/*
 returns size of memory block for a given string length
 function is more safe way to do rounding up than define
*/
size_t str_maxlen2blksize(size_t len)
{
    size_t blksize = len + sizeof(str_t) + 1;
    /* round up size of memory block to multiple of STR_ALLOC_INC */
    return (blksize/STR_ALLOC_INC+1)*STR_ALLOC_INC;
}

size_t str_blksize2maxlen(size_t blksize)
{
    return blksize-sizeof(str_t)-1;
}

size_t str_len(char** s)
{
    str_t* str = STR_CONTAINER(s);
    return str->len; 
}

char* str_alloc(size_t len)
{
    size_t blksize = str_maxlen2blksize(len);
    str_t* newstr = malloc(blksize);
#ifdef STR_CHECK_NULL_ALLOCS
    if (newstr==NULL)
        return NULL;
#endif
    newstr->maxlen = str_blksize2maxlen(blksize);
    newstr->len = 0;
    newstr->str = '\0';
    return &(newstr->str);
}

char* str_realloc(char** s, size_t newlen)
{
    str_t* newstr;
    char*  news;

    if (s==NULL || *s==NULL)
        news = str_alloc(newlen);
    else
    {
        str_t* str = STR_CONTAINER(s);
        if(newlen <= str->maxlen)
            return *s;
        news = str_alloc(newlen);
#ifdef STR_CHECK_NULL_ALLOCS
        if (news == NULL)
            return NULL;
#endif
        newstr = STR_CONTAINER(&news);
        newstr->len = str->len;
        memmove(news, *s, str->len + 1);
    }
    return news;
}

void str_free(char** strptr)
{
    str_t *str = STR_CONTAINER(strptr);
    free(str);
    (*strptr) = NULL;
}

char* str_cpy(char** dst, const char* src)
{
    size_t srclen;
    char *newdst;
#ifdef STR_CHECK_NULL_SRC
    if (src==NULL)
        newdst = NULL;
    else 
#endif
    {
        srclen = strlen(src);
        if (*dst==NULL)
            newdst = str_alloc(srclen);
        else
            newdst = str_realloc(dst, srclen);
#ifdef STR_CHECK_NULL_ALLOCS
        if (newdst==NULL)
            return NULL;
#endif
        memmove(newdst, src, srclen+1);
        STR_CONTAINER(&newdst)->len = srclen;
    }
    (*dst) = newdst;
    return newdst;
}

char* str_cat(char** dst, const char* src)
{
    size_t dstlen, srclen, newdstlen;
    char *newdst;
#ifdef STR_CHECK_NULL_DST
    if (dst==NULL)
        return NULL;
    else if(*dst == NULL)
        return NULL; /* can be changed to str_alloc() */
#endif
#ifdef STR_CHECK_NULL_SRC
    if (src==NULL)
        return *dst;
#endif
    dstlen = str_len(dst);
    srclen = strlen(src);
    newdstlen = dstlen + srclen;
    if (newdstlen==0)
        return *dst;
    newdst = str_realloc(dst, newdstlen);
#ifdef STR_CHECK_NULL_ALLOCS
    if (newdst==NULL)
        return NULL;
#endif
    memmove(newdst+dstlen, src, srclen+1); 
    STR_CONTAINER(&newdst)->len = newdstlen;
    (*dst) = newdst;
    return newdst;
}


int str_printf(char** dst, const char* fmt, ...)
{
    return 0;
}


