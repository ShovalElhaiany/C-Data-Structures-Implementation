/*****************************************
 * date: Thu Jun 05 2025                 *
 * name: Shoval Elhaiany                 *
 * code reviewer: Ofir Cohen             *
 *****************************************/

#ifndef C_HASH_TABLE_H
#define C_HASH_TABLE_H

#include <stddef.h> /* size_t */

#define TABLE_SIZE 100
#define MAX_WORD_SIZE 100
#define AMOUNT_OF_WORDS 104334

typedef struct list list_t;
typedef struct node node_t;
typedef struct hash_table hash_table_t;

typedef int (*cmp_func_t)(const void* data, const void* key);
typedef size_t (*hash_func_t)(const void* key);
typedef int (*Action)(void* data, void* params);

/* Create the hash hashTable.
Return value: a pointer to the hashTable.
cmp_func_t != NULL
key != NULL
hashTableSz > 0 */
hash_table_t* Create(cmp_func_t cmp_func /*1 = TRUE  0 = FALSE*/,
                     hash_func_t hash_func, size_t hashTableSz);

/* Destroy the hashTable.
Note: It is legal to destroy NULL. */
void Destroy(hash_table_t* hashTable);

/* Insert data to the hashTable.
Return value: 0 - for successful insertion, 1 - for failure
hashTable != NULL
data != NULL
Average O(1)*/
int Insert(hash_table_t* hashTable, void* data);

/* Remove the key from the list.
hashTable != NULL
key != NULL
Average O(1)*/
void Remove(hash_table_t* hashTable, const void* key);

/* Find the key in the hashTable.
Return value: data if found, NULL else.
hashTable != NULL.
key != NULL;
Average O(1)*/
void* Find(const hash_table_t* hashTable, const void* key);

/* Calculate the sum of the elemets in the hashTable.
Return value: returns number of inserted data
hashTable != NULL */
size_t Size(const hash_table_t* hashTable);

/* Check if the hashTable is empty.
Return value: 1 if empty, 0 else
hashTable != NULL */
int IsEmpty(const hash_table_t* hashTable);

/* Perform the action function on each element in the hashTable.
Return value: 0 if OK for all, 1 else
hashTable != NULL
act_f != NULL */
int Foreach(const hash_table_t* hashTable, Action action, void* params);

/*----------------------------Advanced----------------------------*/

/* Calculate the load on the hashTable.
Return value: HashSize / hashTableSz
hashTable != NULL */
double Load(const hash_table_t* hashTable);

/* Calculate standard error.
Return value: STD / HashSize
STD = root of: (sum of every element - average) / HashSize.
hashTable != NULL */

/*--------------------------Helper funcs--------------------------*/

void LoadDic(hash_table_t* hash_table);

#endif /* C_HASH_TABLE_H */
