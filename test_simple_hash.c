/*  gcc simple_hash.c test_simple_hash.c -Wall -Wextra -Werror -o test_sh
 * ./test_sh
 */
#include <assert.h> /* assert */
#include <stdio.h> /* puts */

#include "simple_hash.h"

void new_insert_get_destroy(void){
    /* our simple hash table */
    struct sh_table *table = 0;

    /* some keys */
    char *key_1 = "bbbbb";
    char *key_2 = "aaaaa";
    char *key_3 = "ccccc";

    /* some data */
    int data_1 = 1;
    int data_2 = 2;
    int data_3 = 3;

    /* temporary data pointer used for testing get */
    int *data = 0;


    puts("\ntesting basic functionality");

    puts("testing new");
    table = sh_new(32);
    assert(table);
    assert( 32 == table->size );
    assert( 0 == table->n_elems );


    puts("testing insert and get");
    puts("one insert");
    assert( sh_insert(table, key_1, &data_1) );
    assert( 1 == table->n_elems );
    assert( 0 == sh_get(table, key_2) );
    assert( 0 == sh_get(table, key_3) );

    puts("one get");
    data = sh_get(table, key_1);
    assert(data);
    assert( data_1 == *data );


    puts("two insert");
    assert( sh_insert(table, key_2, &data_2) );
    assert( 2 == table->n_elems );
    assert( 0 == sh_get(table, key_3) );

    puts("two get");
    data = sh_get(table, key_2);
    assert(data);
    assert( data_2 == *data );


    puts("three insert");
    assert( sh_insert(table, key_3, &data_3) );
    assert( 3 == table->n_elems );

    puts("three get");
    data = sh_get(table, key_3);
    assert(data);
    assert( data_3 == *data );


    assert( sh_destroy(table, 1, 0) );
}

void set(void){
    /* our simple hash table */
    struct sh_table *table = 0;

    /* some keys */
    char *key_1 = "rhubarb";
    char *key_2 = "carrot";
    char *key_3 = "potato";

    /* some data */
    int data_1 = 1;
    int data_2 = 2;
    int data_3 = 3;

    /* some data we override with */
    int new_data_1 = 14;
    int new_data_2 = 15;
    int new_data_3 = 16;


    /* temporary data pointer used for testing get */
    int *data = 0;

    puts("\ntesting set functionality");

    puts("creating table");
    table = sh_new(32);
    assert(table);
    assert( 32 == table->size );
    assert( 0 == table->n_elems );


    puts("inserting some data");
    assert( sh_insert(table, key_1, &data_1) );
    assert( 1 == table->n_elems );
    assert( 0 == sh_get(table, key_2) );
    assert( 0 == sh_get(table, key_3) );

    data = sh_get(table, key_1);
    assert(data);
    assert( data_1 == *data );


    assert( sh_insert(table, key_2, &data_2) );
    assert( 2 == table->n_elems );
    assert( 0 == sh_get(table, key_3) );

    data = sh_get(table, key_2);
    assert(data);
    assert( data_2 == *data );


    assert( sh_insert(table, key_3, &data_3) );
    assert( 3 == table->n_elems );

    data = sh_get(table, key_3);
    assert(data);
    assert( data_3 == *data );


    puts("testing set");
    puts("testing set failure for non-existing key");
    data = sh_set(table, "foobarr", &data_1);
    assert( 0 == data );

    puts("two set");
    data = sh_set(table, key_2, &new_data_2);
    assert(data);
    assert( *data == data_2 );
    assert( 3 == table->n_elems );

    data = sh_get(table, key_2);
    assert(data);
    assert( *data == new_data_2 );

    puts("three set");
    data = sh_set(table, key_3, &new_data_3);
    assert(data);
    assert( *data == data_3 );
    assert( 3 == table->n_elems );

    data = sh_get(table, key_3);
    assert(data);
    assert( *data == new_data_3 );

    puts("one set");
    data = sh_set(table, key_1, &new_data_1);
    assert(data);
    assert( *data == data_1 );
    assert( 3 == table->n_elems );

    data = sh_get(table, key_1);
    assert(data);
    assert( *data == new_data_1 );


    assert( sh_destroy(table, 1, 0) );
}

void delete(void){
    /* our simple hash table */
    struct sh_table *table = 0;

    /* some keys */
    char *key_1 = "bacon";
    char *key_2 = "chicken";
    char *key_3 = "pork";

    /* some data */
    int data_1 = 1;
    int data_2 = 2;
    int data_3 = 3;

    /* temporary data pointer used for testing get */
    int *data = 0;

    puts("\ntesting delete functionality ");

    puts("creating a table");
    table = sh_new(32);
    assert(table);
    assert( 32 == table->size );
    assert( 0 == table->n_elems );


    puts("inserting some data");
    assert( sh_insert(table, key_1, &data_1) );
    assert( 1 == table->n_elems );
    assert( 0 == sh_get(table, key_2) );
    assert( 0 == sh_get(table, key_3) );

    data = sh_get(table, key_1);
    assert(data);
    assert( data_1 == *data );


    assert( sh_insert(table, key_2, &data_2) );
    assert( 2 == table->n_elems );
    assert( 0 == sh_get(table, key_3) );

    data = sh_get(table, key_2);
    assert(data);
    assert( data_2 == *data );


    assert( sh_insert(table, key_3, &data_3) );
    assert( 3 == table->n_elems );

    data = sh_get(table, key_3);
    assert(data);
    assert( data_3 == *data );


    puts("testing delete");
    puts("one delete");
    data = sh_delete(table, key_1);
    assert(data);
    assert(*data == data_1);
    assert( 2 == table->n_elems );

    /* should not be able to re-delete */
    data = sh_delete(table, key_1);
    assert(! data);


    puts("two delete");
    data = sh_delete(table, key_3);
    assert(data);
    assert(*data == data_3);
    assert( 1 == table->n_elems );

    /* should not be able to re-delete */
    data = sh_delete(table, key_3);
    assert(! data);


    puts("three delete");
    data = sh_delete(table, key_2);
    assert(data);
    assert(*data == data_2);
    assert( 0 == table->n_elems );

    /* should not be able to re-delete */
    data = sh_delete(table, key_2);
    assert(! data);


    assert( sh_destroy(table, 1, 0) );
}

void collision(void){
    /* our simple hash table */
    struct sh_table *table = 0;

    /* some keys */
    char *key_1 = "bacon";
    char *key_2 = "chicken";
    char *key_3 = "pork";
    char *key_4 = "pig";
    char *key_5 = "lettuce";
    char *key_6 = "beetroot";
    char *key_7 = "chocolate";
    char *key_8 = "frying pan";
    char *key_9 = "a4 paper";

    /* some data */
    int data_1 = 1;
    int data_2 = 2;
    int data_3 = 3;
    int data_4 = 4;
    int data_5 = 5;
    int data_6 = 6;
    int data_7 = 7;
    int data_8 = 8;
    int data_9 = 9;

    /* temporary data pointer used for testing get */
    int *data = 0;

    puts("\ntesting collision behavior ");

    puts("creating a table");
    table = sh_new(1);
    assert(table);
    assert( 1 == table->size );
    assert( 0 == table->n_elems );


    puts("inserting some data");
    assert( sh_insert(table, key_1, &data_1) );
    assert( 1 == table->n_elems );
    data = sh_get(table, key_1);
    assert(data);
    assert( data_1 == *data );


    assert( sh_insert(table, key_2, &data_2) );
    assert( 2 == table->n_elems );
    data = sh_get(table, key_2);
    assert(data);
    assert( data_2 == *data );


    assert( sh_insert(table, key_3, &data_3) );
    assert( 3 == table->n_elems );
    data = sh_get(table, key_3);
    assert(data);
    assert( data_3 == *data );

    assert( sh_insert(table, key_4, &data_4) );
    assert( 4 == table->n_elems );
    data = sh_get(table, key_4);
    assert(data);
    assert( data_4 == *data );

    assert( sh_insert(table, key_5, &data_5) );
    assert( 5 == table->n_elems );
    data = sh_get(table, key_5);
    assert(data);
    assert( data_5 == *data );

    assert( sh_insert(table, key_6, &data_6) );
    assert( 6 == table->n_elems );
    data = sh_get(table, key_6);
    assert(data);
    assert( data_6 == *data );

    assert( sh_insert(table, key_7, &data_7) );
    assert( 7 == table->n_elems );
    data = sh_get(table, key_7);
    assert(data);
    assert( data_7 == *data );

    assert( sh_insert(table, key_8, &data_8) );
    assert( 8 == table->n_elems );
    data = sh_get(table, key_8);
    assert(data);
    assert( data_8 == *data );

    assert( sh_insert(table, key_9, &data_9) );
    assert( 9 == table->n_elems );
    data = sh_get(table, key_9);
    assert(data);
    assert( data_9 == *data );

    assert( 9 == table->n_elems );

    puts("testing we can still get everything out");

    data = sh_get(table, key_3);
    assert(data);
    assert( data_3 == *data );

    data = sh_get(table, key_1);
    assert(data);
    assert( data_1 == *data );

    data = sh_get(table, key_2);
    assert(data);
    assert( data_2 == *data );

    data = sh_get(table, key_4);
    assert(data);
    assert( data_4 == *data );

    data = sh_get(table, key_8);
    assert(data);
    assert( data_8 == *data );

    data = sh_get(table, key_5);
    assert(data);
    assert( data_5 == *data );

    data = sh_get(table, key_6);
    assert(data);
    assert( data_6 == *data );

    data = sh_get(table, key_7);
    assert(data);
    assert( data_7 == *data );

    data = sh_get(table, key_9);
    assert(data);
    assert( data_9 == *data );


    puts("testing delete collision handling");

    data = sh_delete(table, key_1);
    assert(data);
    assert(*data == data_1);
    assert( 8 == table->n_elems );

    /* should not be able to re-delete */
    data = sh_delete(table, key_1);
    assert(! data);


    data = sh_delete(table, key_3);
    assert(data);
    assert(*data == data_3);
    assert( 7 == table->n_elems );

    /* should not be able to re-delete */
    data = sh_delete(table, key_3);
    assert(! data);


    data = sh_delete(table, key_2);
    assert(data);
    assert(*data == data_2);
    assert( 6 == table->n_elems );

    /* should not be able to re-delete */
    data = sh_delete(table, key_2);
    assert(! data);

    puts("checking post-delete that all items that should be reachable are");

    data = sh_get(table, key_5);
    assert(data);
    assert( data_5 == *data );

    data = sh_get(table, key_8);
    assert(data);
    assert( data_8 == *data );

    data = sh_get(table, key_4);
    assert(data);
    assert( data_4 == *data );

    data = sh_get(table, key_6);
    assert(data);
    assert( data_6 == *data );

    data = sh_get(table, key_9);
    assert(data);
    assert( data_9 == *data );

    data = sh_get(table, key_7);
    assert(data);
    assert( data_7 == *data );

    assert( sh_destroy(table, 1, 0) );
}

void resize(void){
    /* our simple hash table */
    struct sh_table *table = 0;

    /* some keys */
    char *key_1 = "bbbbb";
    char *key_2 = "aaaaa";
    char *key_3 = "ccccc";

    /* some data */
    int data_1 = 1;
    int data_2 = 2;
    int data_3 = 3;

    /* temporary data pointer used for testing get */
    int *data = 0;


    puts("\ntesting resize functionality");

    puts("creating table");
    table = sh_new(3);
    assert(table);
    assert( 3 == table->size );
    assert( 0 == table->n_elems );


    puts("inserting some data");
    assert( sh_insert(table, key_1, &data_1) );
    assert( 1 == table->n_elems );
    assert( 0 == sh_get(table, key_2) );
    assert( 0 == sh_get(table, key_3) );
    data = sh_get(table, key_1);
    assert(data);
    assert( data_1 == *data );


    assert( sh_insert(table, key_2, &data_2) );
    assert( 2 == table->n_elems );
    assert( 0 == sh_get(table, key_3) );
    data = sh_get(table, key_2);
    assert(data);
    assert( data_2 == *data );


    assert( sh_insert(table, key_3, &data_3) );
    assert( 3 == table->n_elems );
    data = sh_get(table, key_3);
    assert(data);
    assert( data_3 == *data );


    puts("testing resize");
    assert( sh_resize(table, 10) );
    assert( 3  == table->n_elems );
    assert( 10 == table->size );

    puts("testing we can still fetch all the old values");
    data = sh_get(table, key_3);
    assert(data);
    assert( data_3 == *data );

    data = sh_get(table, key_2);
    assert(data);
    assert( data_2 == *data );

    data = sh_get(table, key_1);
    assert(data);
    assert( data_1 == *data );

    assert( sh_destroy(table, 1, 0) );
}

int main(void){
    new_insert_get_destroy();

    set();

    delete();

    collision();

    resize();

    puts("\nsuccess!");

    return 0;
}

