#include "iterator.h"
#include <stdlib.h>

typedef struct it_data {
    long next;
    long size;
    void **elements;
} ItData;

static int it_hasNext(const Iterator *it) {
    ItData *itd = (ItData *)(it->self);

    return (itd->next < itd->size) ? 1 : 0;
}

static int it_next(const Iterator *it, void **element) {
    ItData *itd = (ItData *)(it->self);
    int status = 0;

    if (itd->next < itd->size) {
        *element = itd->elements[itd->next++];
        status = 1;
    }
    return status;
}

static void it_destroy(const Iterator *it) {
    ItData *itd = (ItData *)(it->self);

    free(itd->elements);
    free(itd);
    free((void *)it);
}

static Iterator template = {NULL, it_hasNext, it_next, it_destroy};

const Iterator *Iterator_create(long size, void **elements) {
    Iterator *it = (Iterator *)malloc(sizeof(Iterator));

    if (it != NULL) {
        ItData *itd = (ItData *)malloc(sizeof(ItData));

        if (itd != NULL) {
            itd->next = 0L;
            itd->size = size;
            itd->elements = elements;
            *it = template;
            it->self = itd;
        } else {
            free(it);
            it = NULL;
        }
    }
    return it;
}
