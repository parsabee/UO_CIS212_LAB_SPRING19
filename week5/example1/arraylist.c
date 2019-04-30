/* BSD Header removed to save space */

/*
 * implementation for generic array list
 */

#include "arraylist.h"
#include <stdlib.h>

#define DEFAULT_CAPACITY 10L

typedef struct al_data {
    long capacity;
    long size;
    void **theArray;
} AlData;

/*
 * traverses arraylist, calling freeFxn on each element
 */
static void purge(AlData *ald, void (*freeFxn)(void *element)) {

    if (freeFxn != NULL) {
        long i;

        for (i = 0L; i < ald->size; i++) {
            (*freeFxn)(ald->theArray[i]); /* user frees element storage */
            ald->theArray[i] = NULL;
        }
    }
}

static void al_destroy(const ArrayList *al, void (*freeFxn)(void *element)) {
    AlData *ald = (AlData *)(al->self);
    purge(ald, freeFxn);
    free(ald->theArray);		  /* we free array of pointers */
    free(ald);
    free((void *)al);			  /* we free the ArrayList struct */
}

static int al_add(const ArrayList *al, void *element) {
    AlData *ald = (AlData *)(al->self);
    int status = 1;

    if (ald->capacity <= ald->size) {	/* need to reallocate */
        size_t nbytes = 2 * ald->capacity * sizeof(void *);
        void **tmp = (void **)realloc(ald->theArray, nbytes);
        if (tmp == NULL)
            status = 0;	/* allocation failure */
        else {
            ald->theArray = tmp;
            ald->capacity *= 2;
        }
    }
    if (status)
        ald->theArray[ald->size++] = element;
    return status;
}

static void al_clear(const ArrayList *al, void (*freeFxn)(void *element)) {
    AlData *ald = (AlData *)(al->self);
    purge(ald, freeFxn);
    ald->size = 0L;
}

static int al_ensureCapacity(const ArrayList *al, long minCapacity) {
    AlData *ald = (AlData *)(al->self);
    int status = 1;

    if (ald->capacity < minCapacity) {	/* must extend */
        void **tmp = (void **)realloc(ald->theArray, minCapacity * sizeof(void *));
        if (tmp == NULL)
            status = 0;	/* allocation failure */
        else {
            ald->theArray = tmp;
            ald->capacity = minCapacity;
        }
    }
    return status;
}

int al_get(const ArrayList *al, long index, void **element) {
    AlData *ald = (AlData *)(al->self);
    int status = 0;

    if (index >= 0L && index < ald->size) {
        *element = ald->theArray[index];
        status = 1;
    }
    return status;
}

static int al_insert(const ArrayList *al, long index, void *element) {
    AlData *ald = (AlData *)(al->self);
    int status = 1;

    if (index > ald->size)
        return 0;				/* 0 <= index <= size */
    if (ald->capacity <= ald->size) {	/* need to reallocate */
        size_t nbytes = 2 * ald->capacity * sizeof(void *);
        void **tmp = (void **)realloc(ald->theArray, nbytes);
        if (tmp == NULL)
            status = 0;	/* allocation failure */
        else {
            ald->theArray = tmp;
            ald->capacity *= 2;
        }
    }
    if (status) {
        long j;
        for (j = ald->size; j > index; j--)		/* slide items up */
            ald->theArray[j] = ald->theArray[j-1];
        ald->theArray[index] = element;
        ald->size++;
    }
    return status;
}

static int al_isEmpty(const ArrayList *al) {
    AlData *ald = (AlData *)(al->self);
    return (ald->size == 0L);
}

static int al_remove(const ArrayList *al, long index, void **element) {
    AlData *ald = (AlData *)(al->self);
    int status = 0;
    long j;

    if (index >= 0L && index < ald->size) {
        *element = ald->theArray[index];
        for (j = index + 1; j < ald->size; j++)
            ald->theArray[index++] = ald->theArray[j];
        ald->size--;
        status = 1;
    }
    return status;
}

static int al_set(const ArrayList *al, long index, void *element, void **previous) {
    AlData *ald = (AlData *)(al->self);
    int status = 0;

    if (index >= 0L && index < ald->size) {
        *previous = ald->theArray[index];
        ald->theArray[index] = element;
        status = 1;
    }
    return status;
}

static long al_size(const ArrayList *al) {
    AlData *ald = (AlData *)(al->self);
    return ald->size;
}

/*
 * local function that duplicates the array of void * pointers on the heap
 *
 * returns pointer to duplicate array or NULL if malloc failure
 */
static void **arraydupl(AlData *ald) {
    void **tmp = NULL;
    if (ald->size > 0L) {
        size_t nbytes = ald->size * sizeof(void *);
        tmp = (void **)malloc(nbytes);
        if (tmp != NULL) {
            long i;

            for (i = 0; i < ald->size; i++)
                tmp[i] = ald->theArray[i];
        }
    }
    return tmp;
}

static void **al_toArray(const ArrayList *al, long *len) {
    AlData *ald = (AlData *)al->self;
    void **tmp = arraydupl(ald);

    if (tmp != NULL)
        *len = ald->size;
    return tmp;
}

static int al_trimToSize(const ArrayList *al) {
    AlData *ald = (AlData *)al->self;
    int status = 0;

    void **tmp = (void **)realloc(ald->theArray, ald->size * sizeof(void *));
    if (tmp != NULL) {
        status = 1;
        ald->theArray = tmp;
        ald->capacity = ald->size;
    }
    return status;
}

static const Iterator *al_itCreate(const ArrayList *al) {
    AlData *ald = (AlData *)al->self;
    const Iterator *it = NULL;
    void **tmp = arraydupl(ald);

    if (tmp != NULL) {
        it = Iterator_create(ald->size, tmp);
        if (it == NULL)
            free(tmp);
    }
    return it;
}

static ArrayList template = {NULL, al_destroy, al_add, al_clear,
                             al_ensureCapacity, al_get, al_insert, al_isEmpty,
                             al_remove, al_set, al_size, al_toArray,
                             al_trimToSize, al_itCreate};

const ArrayList *ArrayList_create(long capacity) {
    ArrayList *al = (ArrayList *)malloc(sizeof(ArrayList));

    if (al != NULL) {
        AlData *ald = (AlData *)malloc(sizeof(AlData));
        if (ald != NULL) {
            long cap;
            void **array = NULL;

            cap = (capacity <= 0) ? DEFAULT_CAPACITY : capacity;
            array = (void **) malloc(cap * sizeof(void *));
            if (array != NULL) {
                ald->capacity = cap;
                ald->size = 0L;
                ald->theArray = array;
                *al = template;
                al->self = ald;
            } else {
                free(ald);
                free(al);
                al = NULL;
            }
        } else {
            free(al);
            al = NULL;
        }
    }
    return al;
}
