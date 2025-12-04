/*****************************************
 * date: Thu Jun 05 2025                 *
 * name: Shoval Elhaiany                 *
 * code reviewer: Ofir Cohen             *
 *****************************************/

#include "../include/c_hash_table.h"
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, free */
#include <string.h> /* strcmp, strcpy */
#include <assert.h> /* assert */

#define TEST_SIZE 10
#define SMALL_TABLE_SIZE 5
#define LARGE_TABLE_SIZE 100

/* Test data structure */
typedef struct test_data
{
	int key;
	char* value;
} test_data_t;

/*========================== HELPER FUNCTIONS ============================*/

/* Comparison function for integers */
int IntCmp(const void* data, const void* key)
{
	int data_val = *(int*) data;
	int key_val = *(int*) key;
	return (data_val == key_val);
}

/* Comparison function for strings */
int StrCmp(const void* data, const void* key)
{
	return strcmp((char*) data, (char*) key) == 0;
}

/* Comparison function for test_data structure */
int TestDataCmp(const void* data, const void* key)
{
	test_data_t* test_data = (test_data_t*) data;
	int key_val = *(int*) key;
	return (test_data->key == key_val);
}

/* Simple hash function for integers */
size_t IntHash(const void* key)
{
	return (*(int*) key);
}

/* Simple hash function for strings */
size_t StrHash(const void* key)
{
	char* str = (char*) key;
	size_t hash = 0;
	while (*str)
	{
		hash = hash * 31 + *str;
		str++;
	}
	return hash;
}

/* Hash function for test_data structure */
size_t TestDataHash(const void* key)
{
	return (*(int*) key);
}

/* Action function for counting elements */
int CountAction(void* data, void* params)
{
	int* counter = (int*) params;
	(*counter)++;
	return 0;
}

/* Action function for printing integers */
int PrintIntAction(void* data, void* params)
{
	printf("%d ", *(int*) data);
	return 0;
}

/* Action function for printing strings */
int PrintStrAction(void* data, void* params)
{
	printf("%s ", (char*) data);
	return 0;
}

/* Action function that stops at specific value */
int StopAtValueAction(void* data, void* params)
{
	int* stop_value = (int*) params;
	int current_value = *(int*) data;

	if (current_value == *stop_value)
	{
		return 1; /* Stop iteration */
	}
	return 0; /* Continue */
}

/*============================= TEST FUNCTIONS =============================*/

void TestCreate()
{
	printf("Testing Create function...\n");

	/* Test normal creation */
	hash_table_t* ht = Create(IntCmp, IntHash, TEST_SIZE);
	assert(ht != NULL);
	assert(Size(ht) == 0);
	assert(IsEmpty(ht) == 1);
	Destroy(ht);

	/* Test with different table sizes */
	ht = Create(StrCmp, StrHash, LARGE_TABLE_SIZE);
	assert(ht != NULL);
	Destroy(ht);

	printf("Create function tests passed!\n\n");
}

void TestDestroy()
{
	printf("Testing Destroy function...\n");

	/* Test destroying empty hash table */
	hash_table_t* ht = Create(IntCmp, IntHash, TEST_SIZE);
	Destroy(ht);

	/* Test destroying hash table with elements */
	ht = Create(IntCmp, IntHash, TEST_SIZE);
	int values[] = {1, 2, 3, 4, 5};
	for (int i = 0; i < 5; i++)
	{
		Insert(ht, &values[i]);
	}
	Destroy(ht);

	printf("Destroy function tests passed!\n\n");
}

void TestInsert()
{
	printf("Testing Insert function...\n");

	hash_table_t* ht = Create(IntCmp, IntHash, TEST_SIZE);
	int values[] = {1, 2, 3, 4, 5};

	/* Test inserting elements */
	for (int i = 0; i < 5; i++)
	{
		int result = Insert(ht, &values[i]);
		assert(result == 0); /* Success */
		assert(Size(ht) == i + 1);
		assert(IsEmpty(ht) == 0);
	}

	/* Test inserting duplicate values */
	int result = Insert(ht, &values[0]);
	assert(result == 0);   /* Should still succeed */
	assert(Size(ht) == 6); /* Size should increase */

	Destroy(ht);
	printf("Insert function tests passed!\n\n");
}

void TestFind()
{
	printf("Testing Find function...\n");

	hash_table_t* ht = Create(IntCmp, IntHash, TEST_SIZE);
	int values[] = {1, 2, 3, 4, 5};

	/* Insert test values */
	for (int i = 0; i < 5; i++)
	{
		Insert(ht, &values[i]);
	}

	/* Test finding existing elements */
	for (int i = 0; i < 5; i++)
	{
		void* found = Find(ht, &values[i]);
		assert(found != NULL);
		assert(*(int*) found == values[i]);
	}

	/* Test finding non-existing element */
	int non_existing = 999;
	void* not_found = Find(ht, &non_existing);
	assert(not_found == NULL);

	Destroy(ht);
	printf("Find function tests passed!\n\n");
}

void TestRemove()
{
	printf("Testing Remove function...\n");

	hash_table_t* ht = Create(IntCmp, IntHash, TEST_SIZE);
	int values[] = {1, 2, 3, 4, 5};

	/* Insert test values */
	for (int i = 0; i < 5; i++)
	{
		Insert(ht, &values[i]);
	}

	size_t initial_size = Size(ht);

	/* Test removing existing elements */
	Remove(ht, &values[2]); /* Remove 33 */
	assert(Size(ht) == initial_size - 1);
	assert(Find(ht, &values[2]) == NULL);

	/* Test removing non-existing element */
	int non_existing = 999;
	Remove(ht, &non_existing);
	assert(Size(ht) == initial_size - 1); /* Size shouldn't change */

	/* Test removing all elements */
	for (int i = 0; i < 5; i++)
	{
		if (i != 2) /* Skip already removed element */
		{
			Remove(ht, &values[i]);
		}
	}
	assert(Size(ht) == 0);
	assert(IsEmpty(ht) == 1);

	Destroy(ht);
	printf("Remove function tests passed!\n\n");
}

void TestSizeAndIsEmpty()
{
	printf("Testing Size and IsEmpty functions...\n");

	hash_table_t* ht = Create(IntCmp, IntHash, TEST_SIZE);

	/* Test empty hash table */
	assert(Size(ht) == 0);
	assert(IsEmpty(ht) == 1);

	/* Test after inserting elements */
	int values[] = {1, 2, 3, 4, 5};
	for (int i = 0; i < 5; i++)
	{
		Insert(ht, &values[i]);
		assert(Size(ht) == i + 1);
		assert(IsEmpty(ht) == 0);
	}

	/* Test after removing elements */
	for (int i = 0; i < 5; i++)
	{
		Remove(ht, &values[i]);
		assert(Size(ht) == 5 - i - 1);
	}
	assert(IsEmpty(ht) == 1);

	Destroy(ht);
	printf("Size and IsEmpty functions tests passed!\n\n");
}

void TestForeach()
{
	printf("Testing Foreach function...\n");

	hash_table_t* ht = Create(IntCmp, IntHash, TEST_SIZE);
	int values[] = {10, 20, 30, 40, 50};

	/* Insert test values */
	for (int i = 0; i < 5; i++)
	{
		Insert(ht, &values[i]);
	}

	/* Test counting elements */
	int counter = 0;
	int result = Foreach(ht, CountAction, &counter);
	assert(result == 0);
	assert(counter == 5);

	/* Test early termination */
	int stop_value = 30;
	result = Foreach(ht, StopAtValueAction, &stop_value);
	assert(result == 1); /* Should return 1 when stopped early */

	printf("Elements in hash table: ");
	Foreach(ht, PrintIntAction, NULL);
	printf("\n");

	Destroy(ht);
	printf("Foreach function tests passed!\n\n");
}

void TestLoad()
{
	printf("Testing Load function...\n");

	hash_table_t* ht = Create(IntCmp, IntHash, SMALL_TABLE_SIZE);

	/* Test empty hash table */
	double load = Load(ht);
	assert(load == 0.0);

	/* Test with elements */
	int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	for (int i = 0; i < 10; i++)
	{
		Insert(ht, &values[i]);
		load = Load(ht);
		double expected = (double) (i + 1) / SMALL_TABLE_SIZE;
		assert(load == expected);
	}

	printf("Final load factor: %.2f\n", load);

	Destroy(ht);
	printf("Load function tests passed!\n\n");
}

void TestStringHashTable()
{
	printf("Testing with string data...\n");

	hash_table_t* ht = Create(StrCmp, StrHash, TEST_SIZE);
	char* words[] = {"hello", "world", "hash", "table", "test"};

	/* Insert strings */
	for (int i = 0; i < 5; i++)
	{
		Insert(ht, words[i]);
	}

	/* Test finding strings */
	for (int i = 0; i < 5; i++)
	{
		char* found = (char*) Find(ht, words[i]);
		assert(found != NULL);
		assert(strcmp(found, words[i]) == 0);
	}

	/* Test non-existing string */
	char* not_found = (char*) Find(ht, "nonexistent");
	assert(not_found == NULL);

	printf("Strings in hash table: ");
	Foreach(ht, PrintStrAction, NULL);
	printf("\n");

	Destroy(ht);
	printf("String hash table tests passed!\n\n");
}

void TestComplexData()
{
	printf("Testing with complex data structures...\n");

	hash_table_t* ht = Create(TestDataCmp, TestDataHash, TEST_SIZE);
	test_data_t test_items[5];

	/* Initialize test data */
	for (int i = 0; i < 5; i++)
	{
		test_items[i].key = i * 10;
		test_items[i].value = malloc(20);
		sprintf(test_items[i].value, "Value_%d", i);
		Insert(ht, &test_items[i]);
	}

	/* Test finding complex data */
	for (int i = 0; i < 5; i++)
	{
		int search_key = i * 10;
		test_data_t* found = (test_data_t*) Find(ht, &search_key);
		assert(found != NULL);
		assert(found->key == search_key);
		printf("Found: key=%d, value=%s\n", found->key, found->value);
	}

	/* Clean up */
	for (int i = 0; i < 5; i++)
	{
		free(test_items[i].value);
	}

	Destroy(ht);
	printf("Complex data tests passed!\n\n");
}

void TestEdgeCases()
{
	printf("Testing edge cases...\n");

	/* Test with table size 1 */
	hash_table_t* ht = Create(IntCmp, IntHash, 1);
	int values[] = {1, 2, 3, 4, 5};

	for (int i = 0; i < 5; i++)
	{
		Insert(ht, &values[i]);
	}

	assert(Size(ht) == 5);
	assert(Load(ht) == 5.0);

	/* All elements should be findable even in single bucket */
	for (int i = 0; i < 5; i++)
	{
		assert(Find(ht, &values[i]) != NULL);
	}

	Destroy(ht);

	/* Test inserting same value multiple times */
	ht = Create(IntCmp, IntHash, TEST_SIZE);
	int same_value = 42;
	for (int i = 0; i < 3; i++)
	{
		Insert(ht, &same_value);
	}
	assert(Size(ht) == 3); /* Should allow duplicates */

	Destroy(ht);
	printf("Edge cases tests passed!\n\n");
}

void SpellChecker()
{
	char word[MAX_WORD_SIZE];
	hash_table_t* ht = Create(StrCmp, StrHash, TABLE_SIZE);

	LoadDic(ht);

	while (1)
	{
		printf("Please enter a word: \n");
		scanf("%s", word);

		if (Find(ht, word))
		{
			printf("This word is in the dictionary\n\n");
			printf("=============\n\n");
		}
		else
		{
			printf("This word is NOT in the dictionary.\n\n");
			printf("=============\n\n");
		}
	}
}

void RunAllTests()
{
	printf("========== HASH TABLE TESTS ==========\n\n");

	TestCreate();
	TestDestroy();
	TestInsert();
	TestFind();
	TestRemove();
	TestSizeAndIsEmpty();
	TestForeach();
	TestLoad();
	TestStringHashTable();
	TestComplexData();
	TestEdgeCases();

	printf("========== ALL TESTS PASSED! ==========\n");

	SpellChecker();
}

/*================================= MAIN ==================================*/

int main()
{
	RunAllTests();

	/* Optional: Test dictionary loading function */
	printf("\nTesting dictionary loading (if dictionary file exists)...\n");
	hash_table_t* dict_ht = Create(StrCmp, StrHash, TABLE_SIZE);
	if (dict_ht)
	{
		printf("Created hash table for dictionary with size %d\n", TABLE_SIZE);
		printf("Hash table is %s\n", IsEmpty(dict_ht) ? "empty" : "not empty");

		/* Note: LoadDic function would need to be tested with actual dictionary
		 * file */
		/* LoadDic(dict_ht); */
		/* printf("After loading dictionary: size = %zu, load = %.2f\n",
		          Size(dict_ht), Load(dict_ht)); */

		Destroy(dict_ht);
	}

	return 0;
}
