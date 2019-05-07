#ifndef _ITERATOR_H_
#define _ITERATOR_H_

/* BSD header removed to conserve space */

/* interface definition for generic iterator
 *
 * patterned roughly after Java 6 Iterator class
 */

typedef struct iterator Iterator;		/* forward reference */

/* creates an iterator from the supplied arguments; it is for use by the
 * iterator factory methods in ADTs
 *
 * NB - iterator assumes responsibility for elements[] if create is successful
 * i.e. it_destroy will free the array of pointers
 *
 * returns pointer to iterator if successful, NULL otherwise
 */
const Iterator *Iterator_create(long size, void **elements);

/* now define struct iterator */
struct iterator {
    /* the private data of the iterator */
    void *self;

    /* returns 1/0 if the iterator has a next element */
    int (*hasNext)(const Iterator *self);

    /* returns the next element from the iterator in `*element'
     *
     * returns 1 if successful, 0 if unsuccessful (no next element)
     */
    int (*next)(const Iterator *self, void **element);

    /* destroys the iterator */
    void (*destroy)(const Iterator *self);
};

#endif /* _ITERATOR_H_ */
