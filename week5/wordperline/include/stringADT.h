#ifndef _STRINGADT_H_
#define _STRINGADT_H_
/*
 * BSD Header removed to conserve space.
 * all other comments removed to conserve space.
 */
#include "arraylist.h" /* needed for split method */

typedef struct string String; /* forward reference */
const String *String_create(char *str);
struct string {
    void *self;
/* manager methods (additional constructors and destructor) */
    const String *(*copy)(const String *str);
    const String *(*slice)(const String *str, int begin, int end);
    void (*destroy)(const String *str);
/* mutator methods (change the String) */
    int (*append)(const String *str, char *suffix);
    int (*assign)(const String *str, int chr, int index);
    int (*clear)(const String *str);
    int (*insert)(const String *str, char *substr, int index);
    void (*lower)(const String *str);
    void (*lStrip)(const String *str);
    int (*remove)(const String *str, int index);
    int (*replace)(const String *str, char *old, char *new);
    void (*rStrip)(const String *str);
    void (*strip)(const String *str);
    void (*upper)(const String *str);
/* accessor methods (tell you about the String) */
    int (*compare)(const String *str, const String *other);
    int (*endsWith)(const String *str, char *suffix, int begin, int end);
    int (*index)(const String *str, char *substr, int begin, int end);
    int (*isAlpha)(const String *str);
    int (*isDigit)(const String *str);
    int (*isLower)(const String *str);
    int (*isSpace)(const String *str);
    int (*isUpper)(const String *str);
    int (*len)(const String *str);
    int (*rindex)(const String *str, char *substr, int begin, int end);
    const ArrayList *(*split)(const String *str, char *sep);
    int (*startsWith)(const String *str, char *prefix, int begin, int end);
/* miscellaneous methods */
    char *(*convert)(const String *str);
};
#endif /* _STRINGADT_H_ */
