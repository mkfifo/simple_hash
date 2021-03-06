/* The MIT License (MIT)
 *
 * Author: Chris Hall <followingthepath at gmail dot c0m>
 *
 * Copyright (c) 2015 Chris Hall (cjh)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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
    /* number of elements stored in hash */
    size_t n_elems;
    /* array of pointers to the first bucket in each slot */
    struct sh_entry **entries;
};

/* function to return number of elements
 *
 * returns number on success
 * returns 0 on failure
 */
unsigned int sh_nelems(const struct sh_table *table);

/* takes a char* representing a string
 * and a key_len of it's size
 *
 * will recalculate key_len if 0
 *
 * returns an unsigned long integer hash value on success
 * returns 0 on failure
 */
unsigned long int sh_hash(const char *key, size_t key_len);

/* takes a table and a hash value
 *
 * returns the index into the table for this hash
 * returns 0 on failure (if table is null)
 *
 * note the error value is indistinguishable from the 0th bucket
 * this function can only error if table is null
 * so the caller can distinguish these 2 cases
 */
size_t sh_pos(unsigned long int hash, size_t table_size);

/* allocate and initialise a new sh_table of size size
 *
 * returns pointer on success
 * returns 0 on failure
 */
struct sh_table * sh_new(size_t size);

/* free an existing sh_table
 * this will free all the sh entries stored
 * this will free all the keys (as they are strdup-ed)
 *
 * this will only free the *table pointer if `free_table` is set to 1
 * this will only free the *data pointers if `free_data` is set to 1
 *
 * returns 1 on success
 * returns 0 on failure
 */
unsigned int sh_destroy(struct sh_table *table, unsigned int free_table, unsigned int free_data);

/* initialise an already allocated sh_table to size size
 *
 * returns 1 on success
 * returns 0 on failure
 */
unsigned int sh_init(struct sh_table *table, size_t size);

/* resize an existing table to new_size
 * this will reshuffle all the buckets around
 *
 * you can use this to make a hash larger or smaller
 *
 * returns 1 on success
 * returns 0 on failure
 */
unsigned int sh_resize(struct sh_table *table, size_t new_size);

/* check if the supplied key already exists in this hash
 *
 * returns 1 on success (key exists)
 * returns 0 if key doesn't exist or on failure
 */
unsigned int sh_exists(const struct sh_table *table, const char *key);

/* insert `data` under `key`
 * this will only success if !sh_exists(table, key)
 *
 * returns 1 on success
 * returns 0 on failure
 */
unsigned int sh_insert(struct sh_table *table, const char *key, void *data);

/* update `data` under `key`
 *
 * this will only succeed if sh_exists(table, key)
 *
 * returns old data on success
 * returns 0 on failure
 */
void * sh_update(struct sh_table *table, const char *key, void *data);

/* set `data` under `key`
 *
 * this will perform either an insert or an update
 * depending on if the key already exists
 *
 * returns 1 on success
 * returns 0 on failure
 */
unsigned int sh_set(struct sh_table *table, const char *key, void *data);

/* get `data` stored under `key`
 *
 * returns data on success
 * returns 0 on failure
 */
void * sh_get(const struct sh_table *table, const char *key);

/* delete entry stored under `key`
 *
 * returns data on success
 * returns 0 on failure
 */
void * sh_delete(struct sh_table *table, const char *key);

/* iterate through all key/value pairs in this hash table
 * calling the provided function on each pair.
 *
 * the function is allowed to modify the value but cannot modify the key.
 * the function should not access the hash table in anyway including:
 *  modifying the hash table other than through the value pointer given
 *  calling any other hash table functions
 *
 * the function will be given the value of the `state` pointer for each call,
 * this is useful for passing state between calls to the function as well as
 * for returning results
 *
 * the function should return
 *  1 if it wants the iteration to continue
 *  0 if it wants the iteration to stop
 *
 * returns 1 on success
 * returns 0 on success
 */
unsigned int sh_iterate(struct sh_table *table, void *state, unsigned int (*each)(void *state, const char *key, void **data));

#endif /* ifndef SIMPLE_HASH_H */
