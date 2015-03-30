#ifndef SIMPLE_HASH_H
#define SIMPLE_HASH_H

#include <stddef.h> /* size_t */

struct sh_entry {
    /* hash value for this entry, output of sh_hash(key) */
    unsigned long int hash;
    /* string copied using sh_strdup (defined in simple_hash.c) */
    char *key;
    /* strlen of key, simple cache */
    size_t key_len;
    /* data pointer */
    void *data;
    /* the buckets under a hash are stored as a linked list
     * in no particular order
     */
    struct sh_entry *next;
};

struct sh_table {
    /* number of slots in hash */
    size_t size;
    /* array of pointers to the first bucket in each slot */
    struct sh_entry **entries;
};


/* takes a char* representing a string
 *
 * returns an unsigned long integer hash value on success
 * returns 0 on error
 */
unsigned long int sh_hash(char *key);

/* takes a table and a hash value
 *
 * returns the index into the table for this hash
 * returns 0 on error (if table is null)
 *
 * note the error value is indistinguishable from the 0th bucket
 * this function can only error if table is null
 * so the caller can distinguish these 2 cases
 */
size_t sh_pos(struct sh_table *table, unsigned long int hash);

/* allocate and initialise an ew sh_table of size size
 *
 * returns pointer on success
 * returns 0 on error
 */
struct sh_table * sh_new(size_t size);

/* free an existing sh_table
 * this will free all the sh entries stored
 * this will free all the keys (as they are strdup-ed)
 *
 * this will only free the *data pointers if `free_data` is set to 1
 *
 * returns 1 on success
 * returns 0 on error
 */
unsigned int sh_destroy(struct sh_table *table, unsigned int free_data);

/* initialise an already allocated sh_table to size size
 *
 * returns 1 on success
 * returns 0 on error
 */
unsigned int sh_init(struct sh_table *table, size_t size);

/* resize an existing table to new_size
 * this will reshuffle all the buckets around
 *
 * returns 1 on success
 * returns 0 on error
 */
unsigned int sh_resize(struct sh_table *table, size_t new_size);

/* check if the supplied key already exists in this hash
 *
 * returns 1 on success (key exists)
 * returns 0 if key doesn't exist or on error
 */
unsigned int sh_exists(struct sh_table *table, char *key);

/* insert `data` under `key`
 * this will only success if !sh_exists(table, key)
 *
 * returns 1 on success
 * returns 0 on error
 */
unsigned int sh_insert(struct sh_table *table, char *key, void *data);

/* set `data` under `key`
 * this will only succeed if sh_exists(table, key)
 *
 * returns old data on success
 * returns 0 on error
 */
void * sh_set(struct sh_table *table, char *key, void *data);

/* get `data` stored under `key`
 *
 * returns data on success
 * returns 0 on error
 */
void * sh_get(struct sh_table *table, char *key);

/* delete entry stored under `key`
 *
 * returns 1 on success
 * returns 0 on error
 */
unsigned int sh_delete(struct sh_table *table, char *key);


#endif // ifndef SIMPLE_HASH_H
