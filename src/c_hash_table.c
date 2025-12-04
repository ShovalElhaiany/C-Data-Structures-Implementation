/*****************************************
 * date: Thu Jun 05 2025                 *
 * name: Shoval Elhaiany                 *
 * code reviewer: Ofir Cohen             *
 *****************************************/

#include "../include/c_hash_table.h"
#include "../include/doubly_linked_list.h"

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include <math.h>   /* sqrt */
#include <stdio.h>  /* FILE, fopen, fgets, fclose */

/* Linux dictionary path and max word size */
#define LINUX_DIC "/home/shoval-elhaiany/Desktop/git/ds/src/words.txt"

/* Hash table structure definition */
struct hash_table
{
	list_t** lists;        /* Array of pointers to doubly linked lists */
	size_t table_size;     /* Number of lists in the hash table */
	size_t num_elements;   /* Total number of elements stored */
	cmp_func_t cmp_func;   /* Comparison function pointer */
	hash_func_t hash_func; /* Hash function pointer */
};
/*======================= DECLARATION OF HELPER FUNCS =======================*/

void LoadDic(hash_table_t* hash_table);

/*================================ API FUNCS ================================*/

hash_table_t* Create(cmp_func_t cmp_func, hash_func_t hash_func,
                     size_t hashTableSz)
{
	size_t i = 0;

	/* Allocate memory for hash table structure */
	hash_table_t* hash_table = (hash_table_t*) malloc(sizeof(hash_table_t));
	if (NULL == hash_table)
		return NULL;

	/* Validate input parameters */
	assert(NULL != cmp_func);
	assert(NULL != hash_func);
	assert(0 < hashTableSz);

	/* Allocate memory for array of list pointers */
	hash_table->lists = (list_t**) malloc(sizeof(list_t*) * hashTableSz);
	if (NULL == hash_table->lists)
	{
		free(hash_table);
		return NULL;
	}

	/* Initialize hash table fields */
	hash_table->table_size = hashTableSz;
	hash_table->num_elements = 0;
	hash_table->cmp_func = cmp_func;
	hash_table->hash_func = hash_func;

	/* Create doubly linked list for each list */
	for (i = 0; i < hashTableSz; ++i)
	{
		hash_table->lists[i] = create();
		if (NULL == hash_table->lists[i])
		{
			/* Clean up previously created lists on failure */
			while (0 < i)
			{
				--i;
				destroy(hash_table->lists[i]);
			}
			free(hash_table->lists);
			free(hash_table);
			return NULL;
		}
	}

	return hash_table;
}

/*===========================================================================*/

void Destroy(hash_table_t* hashTable)
{
	size_t i = 0;

	/* Validate input parameter */
	assert(NULL != hashTable);

	/* Destroy all list lists */
	for (i = 0; i < hashTable->table_size; ++i)
		destroy(hashTable->lists[i]);

	/* Free lists array and hash table structure */
	free(hashTable->lists);
	free(hashTable);
}

/*===========================================================================*/

int Insert(hash_table_t* hashTable, void* data)
{
	size_t index = 0;
	node_t* new_node = NULL;

	/* Validate input parameters */
	assert(NULL != hashTable);
	assert(NULL != data);

	/* Calculate list index using hash function */
	index = hashTable->hash_func(data) % hashTable->table_size;

	/* Insert data at the beginning of the appropriate list */
	new_node =
	    insert(hashTable->lists[index], end(hashTable->lists[index]), data);

	/* Check if insertion was successful */
	if (prev(end(hashTable->lists[index])) != new_node)
	{
		return 1; /* Failure */
	}
	/* Increment element count */
	++hashTable->num_elements;

	return 0; /* Success */
}

/*===========================================================================*/

void Remove(hash_table_t* hashTable, const void* key)
{
	size_t index = 0;
	node_t* node = NULL;

	/* Validate input parameters */
	assert(NULL != hashTable);
	assert(NULL != key);

	/* Calculate list index using hash function */
	index = hashTable->hash_func(key) % hashTable->table_size;

	/* Find the node to remove in the specific list */
	node = find(next(begin(hashTable->lists[index])),
	            end(hashTable->lists[index]), hashTable->cmp_func, key);

	/* Remove node if found */
	if (node)
	{
		removelist(node);
		--hashTable->num_elements;
	}
}

/*===========================================================================*/

void* Find(const hash_table_t* hashTable, const void* key)
{
	size_t index = 0;
	node_t* node = NULL;
	node_t* debug;
	/* Validate input parameters */
	assert(NULL != hashTable);
	assert(NULL != key);

	/* Calculate list index using hash function */
	index = hashTable->hash_func(key) % hashTable->table_size;
	/* Find the node in the specific list */
	node = find(next(begin(hashTable->lists[index])),
	            end(hashTable->lists[index]), hashTable->cmp_func, key);
	/* Return data if found */
	return getdata(node);
}

/*===========================================================================*/

size_t Size(const hash_table_t* hashTable)
{
	/* Validate input parameter */
	assert(NULL != hashTable);

	return hashTable->num_elements;
}

/*===========================================================================*/

int IsEmpty(const hash_table_t* hashTable)
{
	/* Validate input parameter */
	assert(NULL != hashTable);

	return (0 == hashTable->num_elements) ? 1 : 0;
}

/*===========================================================================*/

int Foreach(const hash_table_t* hashTable, Action action, void* params)
{
	size_t i = 0;
	int result = 0;

	/* Validate input parameters */
	assert(NULL != hashTable);
	assert(NULL != action);

	/* Iterate through all lists */
	while (i < hashTable->table_size && 0 == result)
	{
		/* Apply action function to all elements in current list */
		result = foreach (next(begin(hashTable->lists[i])),
		                  end(hashTable->lists[i]), action, params);
		++i;
	}

	return result;
}

/*================================= ADVANCED =================================*/

double Load(const hash_table_t* hashTable)
{
	/* Validate input parameter */
	assert(NULL != hashTable);

	return (double) hashTable->num_elements / (double) hashTable->table_size;
}

// double SD(const hash_table_t* hashTable)
// {
// 	size_t i = 0;
// 	double average = 0.0;
// 	double sum_of_squares = 0.0;
// 	double variance = 0.0;
// 	size_t list_count = 0;

// 	assert(NULL != hashTable);

// 	/* Handle empty hash table */
// 	if (0 == hashTable->num_elements)
// 	{
// 		return 0.0;
// 	}

// 	/* Calculate average number of elements per list */
// 	average = (double) hashTable->num_elements / (double) hashTable->table_size;

// 	/* Calculate sum of squared differences from average */
// 	for (i = 0; i < hashTable->table_size; ++i)
// 	{
// 		list_count = count(hashTable->lists[i]);
// 		sum_of_squares += (list_count - average) * (list_count - average);
// 	}

// 	/* Calculate variance */
// 	variance = sum_of_squares / (double) hashTable->table_size;

// 	/* Return standard deviation normalized by hash size */
// 	return sqrt(variance) / (double) hashTable->num_elements;
// }

/*============================== HELPER FUNCS ==============================*/

void LoadDic(hash_table_t* hash_table)
{
	/* Create a file pointer and open the for reading. */
	FILE* file = fopen(LINUX_DIC, "r");

	/* Buffer to store each word of the file. */
	char word[MAX_WORD_SIZE];

	/* Check if file is opened successfully */
	assert(file != NULL);

	/* Read each word from the file and store it in the 'word' buffer. */
	while (fgets(word, MAX_WORD_SIZE, file))
	{
		word[strcspn(word, "\n")] = '\0';

		char* dup = strdup(word);
		if (dup == NULL)
		{
			continue;
		}
		Insert(hash_table, dup);
	}

	/* Close file. */
	fclose(file);
}
