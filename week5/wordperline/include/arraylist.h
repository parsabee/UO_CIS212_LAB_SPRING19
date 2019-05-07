#ifndef _ARRAYLIST_H_
#define _ARRAYLIST_H_

/* BSD header removed to save space */

#include "iterator.h"                   /* needed for factory method */

/* interface definition for generic arraylist implementation
 *
 * patterned roughly after Java 6 ArrayList generic class
 */

typedef struct arraylist ArrayList;     /* forward reference */

/* create an arraylist with the specified capacity; if capacity == 0, a
 * default initial capacity (10 elements) is used
 *
 * returns a pointer to the array list, or NULL if there are malloc() errors
 */
const ArrayList *ArrayList_create(long capacity);

/* now define struct arraylist */
struct arraylist {
/* the private data of the array list */
    void *self;

/* destroys the arraylist; for each occupied index, if freeFxn != NULL,
 * it is invoked on the element at that position; the storage associated with
 * the arraylist is then returned to the heap
 */
    void (*destroy)(const ArrayList *al, void (*freeFxn)(void *element));

/* appends `element' to the arraylist; if no more room in the list, it is
 * dynamically resized
 *
 * returns 1 if successful, 0 if unsuccessful (malloc errors)
 */
    int (*add)(const ArrayList *al, void *element);

/* clears all elements from the arraylist; for each occupied index,
 * if freeFxn != NULL, it is invoked on the element at that position;
 * any storage associated with the element in the arraylist is then
 * returned to the heap
 *
 * upon return, the arraylist will be empty
 */
    void (*clear)(const ArrayList *al, void (*freeFxn)(void *element));

/* ensures that the arraylist can hold at least `minCapacity' elements
 *
 * returns 1 if successful, 0 if unsuccessful (malloc failure)
 */
    int (*ensureCapacity)(const ArrayList *al, long minCapacity);

/* returns the element at the specified position in this list in `*element'
 *
 * returns 1 if successful, 0 if no element at that position
 */
    int (*get)(const ArrayList *al, long index, void **element);

/* inserts `element' at the specified position in the arraylist;
 * all elements from `i' onwards are shifted one position to the right;
 * if no more room in the list, it is dynamically resized;
 * if the current size of the list is N, legal values of i are in the
 * interval [0, N]
 *
 * returns 1 if successful, 0 if unsuccessful (malloc errors)
 */
    int (*insert)(const ArrayList *al, long index, void *element);

/* returns 1 if arraylist is empty, 0 if it is not */
    int (*isEmpty)(const ArrayList *al);

/* removes the `i'th element from the list, returns the value that
 * occupied that position in `*element'; all elements from [i+1, size-1] are
 * shifted down one position
 *
 * returns 1 if successful, 0 if `i'th position was not occupied
 */
    int (*remove)(const ArrayList *al, long index, void **element);

/* relaces the `i'th element of the arraylist with `element';
 * returns the value that previously occupied that position in `*previous'
 *
 * returns 1 if successful
 * returns 0 if `i'th position not currently occupied
 */
    int (*set)(const ArrayList *al, long index, void *element, void **previous);

/* returns the number of elements in the arraylist */
    long (*size)(const ArrayList *al);

/* returns an array containing all of the elements of the list in
 * proper sequence (from first to last element); returns the length of
 * the list in `*len'
 *
 * returns pointer to void * array of elements, or NULL if malloc failure
 *
 * NB - the caller is responsible for freeing the void * array when finished
 *      with it
 */
    void **(*toArray)(const ArrayList *al, long *len);

/* trims the capacity of the arraylist to be the list's current size
 *
 * returns 1 if successful, 0 if failure (malloc errors)
 */
    int (*trimToSize)(const ArrayList *al);

/* create generic iterator to this arraylist
 *
 * returns pointer to the Iterator or NULL if failure
 */
    const Iterator *(*itCreate)(const ArrayList *al);
};

#endif /* _ARRAYLIST_H_ */
