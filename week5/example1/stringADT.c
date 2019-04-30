/* implementation for String ADT */
#include "stringADT.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/* member data for String instance */
typedef struct st_data {
    int length;
    int size;
    char *buf;
} StData;

#define INCREMENT 1024 /* if we ever have to grow the string, do it
                          by this increment except for replace() */

/*
 * helper function that creates a copy of buf[begin]..buf[end], inclusive,
 * on the heap
 *
 * assumes that begin and end are legal indices into buf
 *
 * returns pointer to the copy, or NULL if malloc() failure
*/
static char *slice_copy(char *buf, int begin, int end) {
    int size = end - begin + 1 + 1; /* +1 for '\0' */
    char *p;

    if ((p = (char *)malloc(size)) != NULL) {
        int i, j;

        for (i = begin, j = 0; i <= end; i++, j++)
            p[j] = buf[i];
        p[j] = '\0';
    }
    return p;
}

static const String *st_copy(const String *str) {
    StData *std = (StData *)str->self;
    String *nstr = (String *)malloc(sizeof(String));

    if (nstr != NULL) {
        StData *nstd = (StData *)malloc(sizeof(StData));

        if (nstd != NULL) {
            nstd->buf = slice_copy(std->buf, 0, std->length - 1);
            if (nstd->buf != NULL) {
                nstd->length = std->length;
                nstd->size = std->size;
                *nstr = *str;
                nstr->self = nstd;
            } else {
                free(nstd);
                free(nstr);
                nstr = NULL;
            }
        } else {
            free(nstr);
            nstr = NULL;
        }
    }
    return nstr;
}

static const String *st_slice(const String *str, int begin, int end) {
    StData *std = (StData *)str->self;
    String *nstr = NULL;

    if (end == 0)
        end = std->length;
    if (begin >= 0 && end <= std->length && begin < end) {
        nstr = (String *)malloc(sizeof(String));
        if (nstr != NULL) {
            StData *nstd = (StData *)malloc(sizeof(StData));

            if (nstd != NULL) {
                nstd->buf = slice_copy(std->buf, begin, end - 1);
                if (nstd->buf != NULL) {
                    nstd->length = strlen(nstd->buf);
                    nstd->size = nstd->length + 1;
                    *nstr = *str;
                    nstr->self = nstd;
                } else {
                    free(nstd);
                    free(nstr);
                    nstr = NULL;
                }
            } else {
                free(nstr);
                nstr = NULL;
            }
        }
    }
    return nstr;
}

static void st_destroy(const String *str) {
    StData *std = (StData *)str->self;

    free(std->buf);
    free(std);
    free((void *)str);
}

static int st_append(const String *str, char *suffix) {
    StData *std = (StData *)str->self;
    int n = strlen(suffix);

    if ((std->length + n + 1) > std->size) {
        int nsize = std->size + ((n > INCREMENT) ? n : INCREMENT);
        char *p = (char *)realloc(std->buf, nsize);

        if (p == NULL)
            return 0;
        std->buf = p;
        std->size = nsize;
    }
    strcpy(std->buf+std->length, suffix);
    std->length = strlen(std->buf);
    return 1;
}

static int st_assign(const String *str, int chr, int index) {
    StData *std = (StData *)str->self;
    int result = 0;

    if (index >= 0 && index < std->length) {
        std->buf[index] = chr;
        result = 1;
    }
    return result;
}

static int st_clear(const String *str) {
    StData *std = (StData *)str->self;

    std->length = 0;
    std->buf[0] = '\0';
    return 1;
}

static int st_insert(const String *str, char *substr, int index) {
    StData *std = (StData *)str->self;
    int n = strlen(substr);
    int i, j;

    if (index < 0 || index > std->length)
        return 0;
    if ((std->length + n + 1) > std->size) {
        int nsize = std->size + ((n > INCREMENT) ? n : INCREMENT);
        char *p = (char *)realloc(std->buf, nsize);

        if (p == NULL)
            return 0;
        std->buf = p;
        std->size = nsize;
    }
    for (i = std->length, j = std->length + n; i >= index; i--, j--)
        std->buf[j] = std->buf[i];
    for (i = 0, j = index; i < n; i++, j++)
        std->buf[j] = substr[i];
    std->length += n;
    return 1;
}

static void st_lower(const String *str) {
    StData *std = (StData *)str->self;
    int i;

    for (i = 0; i < std->length; i++)
        std->buf[i] = tolower(std->buf[i]);
}

static void st_lStrip(const String *str) {
    StData *std = (StData *)str->self;
    int i, j;

    for (i = 0; i < std->length; i++)
        if (! isspace(std->buf[i]))
            break;
    for (j = 0; i < std->length; i++, j++)
        std->buf[j] = std->buf[i];
    std->buf[j] = '\0';
    std->length = strlen(std->buf);
}

static int st_remove(const String *str, int index) {
    StData *std = (StData *)str->self;
    int result = 0, i, j;

    if (index >= 0 && index < std->length) {
        for (j = index, i = index + 1; i < std->length; i++, j++)
            std->buf[j] = std->buf[i];
        std->buf[j] = '\0';
        std->length--;
        result = 1;
    }
    return result;
}

static int st_replace(const String *str, char *old, char *new) {
    StData *std = (StData *)str->self;
    int oldlen = strlen(old);
    int newlen = strlen(new);
    int nold, size;
    char *nbuf;
    int result = 0; /* assume malloc() fails */

    nold = ((std->length) / oldlen) + 1; /* worst case # of matches */
    size = std->size - nold * oldlen + nold * newlen;
    if (size < std->size)
        size = std->size;
    nbuf = (char *)malloc(size);
    if (nbuf != NULL) {
        int i, j;
        i = 0;
        j = 0;
        while (i < std->length) {
            if (strncmp(std->buf+i, old, oldlen) == 0) {
                strncpy(nbuf+j, new, newlen);
                j += newlen;
                i += oldlen;
            } else {
                nbuf[j++] = std->buf[i++];
            }
        }
        nbuf[j] = '\0';
        free(std->buf);
        std->buf = nbuf;
        std->length = j;
        std->size = size;
        result = 1;
    }
    return result;
}

static void st_rStrip(const String *str) {
    StData *std = (StData *)str->self;
    int i;

    for (i = std->length - 1; i >= 0; i--)
        if (! isspace(std->buf[i]))
            break;
    std->buf[i+1] = '\0';
    std->length = strlen(std->buf);
}

static void st_strip(const String *str) {

    st_lStrip(str);
    st_rStrip(str);
}

static void st_upper(const String *str) {
    StData *std = (StData *)str->self;

    int i;
    for (i = 0; i < std->length; i++)
        std->buf[i] = toupper(std->buf[i]);
}

static int st_compare(const String *str, const String *other) {
    StData *std = (StData *)str->self;
    StData *otd = (StData *)other->self;

    return strcmp(std->buf, otd->buf);
}

static int st_endsWith(const String *str, char *suffix, int begin, int end) {
    StData *std = (StData *)str->self;
    int nchars, suflen, result = 0;

    if (end == 0)
        end = std->length;
    nchars = end - begin;
    suflen = strlen(suffix);
    if (nchars >= suflen) {
        if (strncmp(suffix, std->buf + end - suflen, suflen) == 0)
            result = 1;
    }
    return result;
}

static int st_index(const String *str, char *substr, int begin, int end) {
    StData *std = (StData *)str->self;
    int n = strlen(substr);
    int i, j;

    if (end == 0)
        end = std->length;
    for (i = begin, j = end - begin; i < end && j >= n; i++, j--)
        if (strncmp(std->buf + i, substr, n) == 0)
            return i;
    return -1;
}

static int st_isAlpha(const String *str) {
    StData *std = (StData *)str->self;
    int i;

    if (std->length > 0) {
        for (i = 0; i < std->length; i++)
            if (! isalpha(std->buf[i]))
            return 0;
        return 1;
    }
    return 0;
}

static int st_isDigit(const String *str) {
    StData *std = (StData *)str->self;
    int i;

    if (std->length > 0) {
        for (i = 0; i < std->length; i++)
            if (! isdigit(std->buf[i]))
                return 0;
        return 1;
    }
    return 0;
}

static int st_isLower(const String *str) {
    StData *std = (StData *)str->self;
    int i;

    if (std->length > 0) {
        for (i = 0; i < std->length; i++)
            if (! islower(std->buf[i]))
                return 0;
        return 1;
    }
    return 0;
}

static int st_isSpace(const String *str) {
    StData *std = (StData *)str->self;

    int i;
    if (std->length > 0) {
        for (i = 0; i < std->length; i++)
            if (! isspace(std->buf[i]))
                return 0;
        return 1;
    }
    return 0;
}

static int st_isUpper(const String *str) {
    StData *std = (StData *)str->self;
    int i;

    if (std->length > 0) {
        for (i = 0; i < std->length; i++)
            if (! isupper(std->buf[i]))
                return 0;
        return 1;
    }
    return 0;
}

static int st_len(const String *str) {
    StData *std = (StData *)str->self;

    return std->length;
}

static int st_rindex(const String *str, char *substr, int begin, int end) {
    StData *std = (StData *)str->self;
    int n = strlen(substr);
    int i, j;

    if (end == 0)
        end = std->length;
    for (i = end - n, j = end - begin; i >= begin && j >= n; i--, j--)
        if (strncmp(std->buf + i, substr, n) == 0)
            return i;
    return -1;
}

static long st_split_pat(char *s, char *sep, char *elems[]) {
    long i, j;
    int n = strlen(sep);
    char *p, *q, *t, buf[4096];

    i = 0;
    p = s;
    while (*p != '\0') {
        q = strstr(p, sep);
        t = buf;
        if (q == NULL) { /* not found, copy rest of s into buf */
            while ((*t++ = *p++) != '\0')
                ;
        p--; /* went one position too far */
    } else {
        while (p != q)
            *t++ = *p++;
        *t = '\0';
        p += n; /* point at first character past sep */
    }
    if ((t = strdup(buf)) == NULL)
        goto cleanup;
    elems[i++] = t;
    }
    return i;
cleanup:
    for (j = 0; j < i; j++)
        free(elems[j]);
    return 0;
}

static int skipchr(char buf[], char c) {
    int i;

    for (i = 0; buf[i] != '\0'; i++)
        if (buf[i] == c)
            return i;
    return -1;
}

static char *whitespace = " \t\n";
static int getword(char buf[], int i, char word[]) {
    char *p;
    int j = i;

    while (skipchr(whitespace, buf[j]) != -1)
        j++;
    if (buf[j] == '\0')
        return -1;
    p = word;
    while (buf[j] != '\0') {
        if (strchr(whitespace, buf[j]) != NULL)
            break;
        *p++ = buf[j];
        j++;
    }
    *p = '\0';
    return j;
}

static long st_split_white(char *s, char *elems[]) {
    int i, k;
    long j;
    char buf[4096];

    i = 0;
    j = 0;
    for (i = 0; (k = getword(s, i, buf)) != -1; i = k) {
        char *t = strdup(buf);
        if (t == NULL)
            goto cleanup;
        elems[j++] = t;
    }
    return j;
cleanup:
    for (j--; j >= 0; j--)
        free(elems[j]);
    return 0;
}

static const ArrayList *st_split(const String *str, char *sep) {
    const ArrayList *al = NULL;
    char *elems[1000]; /* can't handle more than 1000 words */
    char *s = str->convert(str);
    long i, n;

/*
* note - if sep == "", leading and trailing white space characters are
* ignored
*/

    if (sep[0] != '\0')
        n = st_split_pat(s, sep, elems);
    else
        n = st_split_white(s, elems);
    if (n > 0) {
        al = ArrayList_create(n);
        if (al != NULL) {
            for (i = 0; i < n; i++)
                (void) al->add(al, elems[i]);
        } else {
            for (i = 0; i < n; i++)
                free(elems[i]);
        }
    }
    return al;
}

static int st_startsWith(const String *str, char *prefix, int begin, int end) {
    StData *std = (StData *)str->self;
    int nchars, prelen, result = 0;

    if (end == 0)
        end = std->length;
    nchars = end - begin;
    prelen = strlen(prefix);
    if (nchars >= prelen) {
        if (strncmp(prefix, std->buf + begin, prelen) == 0)
            result = 1;
    }
    return result;
}

static char *st_convert(const String *str) {
    StData *std = (StData *)str->self;

    return std->buf;
}

static String template = {
    NULL, st_copy, st_slice, st_destroy, st_append, st_assign, st_clear, 
    st_insert, st_lower, st_lStrip, st_remove, st_replace, st_rStrip, st_strip,
    st_upper, st_compare, st_endsWith, st_index, st_isAlpha, st_isDigit,
    st_isLower, st_isSpace, st_isUpper, st_len, st_rindex, st_split,
    st_startsWith, st_convert
};

const String *String_create(char *str) {
    String *st = (String *)malloc(sizeof(String));

    if (st != NULL) {
        StData *std = (StData *)malloc(sizeof(StData));

        if (std != NULL) {
            std->length = strlen(str); /* length of str */
            std->size = std->length + 1; /* account for '\0' */
            std->buf = (char *)malloc(std->size);
            if (std->buf != NULL) {
                strcpy(std->buf, str);
                *st = template;
                st->self = std;
            } else {
                free(std);
                free(st);
                st = NULL;
            }
        } else {
            free(st);
            st = NULL;
        }
    }
    return st;
}
