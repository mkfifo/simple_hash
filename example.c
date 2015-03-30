#include "simple_hash.h"

int main(void){
    /* create a hash with 32 buckets */
    struct sh_table *t = sh_new(32);

    /* some data to store */
    int data_1 = 1;
    int data_2 = 2;

    /* return pointer */
    int *data;

    /* insert new data */
    sh_insert(t, "hello", &data_1);
    sh_insert(t, "world", &data_2);

    /* fetch */
    data = sh_get(t, "hello");

    /* delete existing data */
    sh_delete(t, "world");

    /* mutate existing data */
    sh_set(t, "hello", &data_2);

    /* check a key exists */
    if( sh_exists(t, "hello") ){
    }

    /* destroy(table, free_table, free_data) */
    sh_destroy(t,     1,          0);
}
