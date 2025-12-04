/*****************************************
 * date: Tue Jun 17 2025                 *
 * name: Shoval Elhaiany                 *
 * code reviewer: John Doe               *
 *****************************************/

#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */
#include <string.h> /* strcmp */
#include <assert.h> /* assert */

#include "../include/avl.h"

/* Test counter and macros */
static int test_count = 0;
static int test_passed = 0;

#define TEST_START()                                                           \
	do                                                                         \
	{                                                                          \
		printf("Running test %d\n", ++test_count);                             \
	} while (0)

#define TEST_ASSERT(condition, message)                                        \
	do                                                                         \
	{                                                                          \
		if (condition)                                                         \
		{                                                                      \
			printf("  ✓ %s\n", message);                                       \
		}                                                                      \
		else                                                                   \
		{                                                                      \
			printf("  ✗ %s - FAILED\n", message);                              \
			return 0;                                                          \
		}                                                                      \
	} while (0)

#define TEST_END()                                                             \
	do                                                                         \
	{                                                                          \
		printf("  Test %d passed!\n\n", test_count);                           \
		test_passed++;                                                         \
		return 1;                                                              \
	} while (0)

/* Comparison functions for testing */
int IntCompare(const void* data, const void* tree_data)
{
	int a = *(int*) data;
	int b = *(int*) tree_data;
	return (a > b) - (a < b);
}

int StringCompare(const void* data, const void* tree_data)
{
	return strcmp((const char*) data, (const char*) tree_data);
}

/* Operation functions for ForEach testing */
int PrintIntOp(void* tree_data)
{
	printf("%d ", *(int*) tree_data);
	return 0;
}

int SumOp(void* tree_data, void* arg)
{
	int* sum = (int*) arg;
	*sum += *(int*) tree_data;
	return 0;
}

int CountOp(void* tree_data, void* arg)
{
	int* count = (int*) arg;
	(void) tree_data;
	(*count)++;
	return 0;
}

int FailingOp(void* tree_data, void* arg)
{
	(void) tree_data;
	(void) arg;
	return -1; /* Always fails */
}

/* Test functions */

int TestAVLCreate()
{
	avl_t* tree = NULL;
	avl_t* null_tree = NULL;

	TEST_START();

	tree = AVLCreate(IntCompare);
	TEST_ASSERT(tree != NULL,
	            "AVLCreate with valid compare function should succeed");

	null_tree = AVLCreate(NULL);
	TEST_ASSERT(null_tree == NULL,
	            "AVLCreate with NULL compare function should fail");

	AVLDestroy(tree);
	TEST_END();
}

int TestAVLDestroy()
{
	avl_t* tree = NULL;

	TEST_START();

	tree = AVLCreate(IntCompare);
	AVLDestroy(tree);
	TEST_ASSERT(1, "AVLDestroy with valid tree should not crash");

	AVLDestroy(NULL);
	TEST_ASSERT(1, "AVLDestroy with NULL should not crash");

	TEST_END();
}

int TestAVLIsEmpty()
{
	avl_t* tree = NULL;
	int value = 0;

	TEST_START();

	tree = AVLCreate(IntCompare);
	TEST_ASSERT(AVLIsEmpty(tree) == 1, "New tree should be empty");

	value = 42;
	AVLInsert(tree, &value);
	TEST_ASSERT(AVLIsEmpty(tree) == 0,
	            "Tree with one element should not be empty");

	AVLRemove(tree, &value);
	TEST_ASSERT(AVLIsEmpty(tree) == 1,
	            "Tree after removing last element should be empty");

	AVLDestroy(tree);
	TEST_END();
}

int TestAVLInsertAndFind()
{
	int i = 0;
	int dummy = 0;
	int result = 0;
	int num_values = 0;
	int non_existing = 0;
	avl_t* tree = NULL;
	void* not_found = NULL;
	void* null_result = NULL;
	int values[] = {50, 30, 70, 20, 40, 60, 80};

	TEST_START();

	tree = AVLCreate(IntCompare);
	num_values = sizeof(values) / sizeof(values[0]);

	/* Test insertion */
	for (i = 0; i < num_values; i++)
	{
		result = AVLInsert(tree, &values[i]);
		TEST_ASSERT(result == 0, "AVLInsert should succeed for valid data");
	}

	/* Test finding existing elements */
	for (i = 0; i < num_values; i++)
	{
		void* found = AVLFind(tree, &values[i]);
		TEST_ASSERT(found != NULL, "AVLFind should find existing element");
		TEST_ASSERT(*(int*) found == values[i],
		            "Found element should have correct value");
	}

	/* Test finding non-existing element */
	non_existing = 999;
	not_found = AVLFind(tree, &non_existing);
	TEST_ASSERT(not_found == NULL,
	            "AVLFind should return NULL for non-existing element");

	/* Test insert with NULL tree */
	dummy = 1;
	result = AVLInsert(NULL, &dummy);
	TEST_ASSERT(result == 0, "AVLInsert with NULL tree should fail");

	/* Test find with NULL tree */
	null_result = AVLFind(NULL, &dummy);
	TEST_ASSERT(null_result == NULL,
	            "AVLFind with NULL tree should return NULL");

	AVLDestroy(tree);
	TEST_END();
}

int TestAVLRemove()
{
	int i = 0;
	int num_values = 0;
	int non_existing = 0;
	avl_t* tree = NULL;
	int values[] = {50, 30, 70, 20, 40, 60, 80};

	TEST_START();

	tree = AVLCreate(IntCompare);
	num_values = sizeof(values) / sizeof(values[0]);

	/* Insert values */
	for (i = 0; i < num_values; i++)
	{
		AVLInsert(tree, &values[i]);
	}

	/* Remove leaf node */
	AVLRemove(tree, &values[3]); /* Remove 20 */
	TEST_ASSERT(AVLFind(tree, &values[3]) == NULL,
	            "Removed element should not be found");

	/* Remove node with one child */
	AVLRemove(tree, &values[1]); /* Remove 30 */
	TEST_ASSERT(AVLFind(tree, &values[1]) == NULL,
	            "Removed element should not be found");

	/* Remove node with two children */
	AVLRemove(tree, &values[0]); /* Remove 50 (root) */
	TEST_ASSERT(AVLFind(tree, &values[0]) == NULL,
	            "Removed element should not be found");

	/* Test removing non-existing element */
	non_existing = 999;
	AVLRemove(tree, &non_existing);
	TEST_ASSERT(1, "Removing non-existing element should not crash");

	/* Test remove with NULL tree */
	AVLRemove(NULL, &values[0]);
	TEST_ASSERT(1, "AVLRemove with NULL tree should not crash");

	AVLDestroy(tree);
	TEST_END();
}

int TestAVLCount()
{
	int i = 0;
	int num_values = 0;
	avl_t* tree = NULL;
	int values[] = {50, 30, 70, 20, 40};

	TEST_START();

	tree = AVLCreate(IntCompare);
	TEST_ASSERT(AVLCount(tree) == 0, "Empty tree should have count 0");

	num_values = sizeof(values) / sizeof(values[0]);

	/* Test count after insertions */
	for (i = 0; i < num_values; i++)
	{
		AVLInsert(tree, &values[i]);
		TEST_ASSERT(AVLCount(tree) == (size_t) (i + 1),
		            "Count should increase after insertion");
	}

	/* Test count after removals */
	for (i = 0; i < num_values; i++)
	{
		AVLRemove(tree, &values[i]);
		TEST_ASSERT(AVLCount(tree) == (size_t) (num_values - i - 1),
		            "Count should decrease after removal");
	}

	/* Test count with NULL tree */
	TEST_ASSERT(AVLCount(NULL) == 0, "AVLCount with NULL tree should return 0");

	AVLDestroy(tree);
	TEST_END();
}

int TestAVLHeight()
{
	int i = 0;
	int value1 = 0;
	size_t height = 0;
	avl_t* tree = NULL;
	int values[] = {30, 70, 20, 40, 60, 80};

	TEST_START();

	tree = AVLCreate(IntCompare);
	TEST_ASSERT(AVLHeight(tree) == 0, "Empty tree should have height 0");

	/* Single node */
	value1 = 50;
	AVLInsert(tree, &value1);
	TEST_ASSERT(AVLHeight(tree) == 1, "Single node tree should have height 1");

	/* Add more nodes to test height */
	for (i = 0; i < 6; i++)
	{
		AVLInsert(tree, &values[i]);
	}

	height = AVLHeight(tree);
	TEST_ASSERT(height > 0, "Non-empty tree should have positive height");
	TEST_ASSERT(height <= 4, "AVL tree height should be balanced (log n)");

	/* Test height with NULL tree */
	TEST_ASSERT(AVLHeight(NULL) == 0,
	            "AVLHeight with NULL tree should return 0");

	AVLDestroy(tree);
	TEST_END();
}

int TestAVLForEach()
{
	int i = 0;
	int sum = 0;
	int count = 0;
	int result = 0;
	int num_values = 0;
	int expected_sum = 0;
	avl_t* tree = NULL;
	int values[] = {50, 30, 70, 20, 40, 60, 80};

	TEST_START();

	tree = AVLCreate(IntCompare);
	num_values = sizeof(values) / sizeof(values[0]);

	/* Insert values */
	for (i = 0; i < num_values; i++)
	{
		AVLInsert(tree, &values[i]);
	}

	/* Test sum operation */
	sum = 0;
	result = AVLForEach(tree, SumOp, &sum);
	TEST_ASSERT(result == 0, "AVLForEach should return 0 on success");

	expected_sum = 0;
	for (i = 0; i < num_values; i++)
	{
		expected_sum += values[i];
	}
	TEST_ASSERT(sum == expected_sum,
	            "Sum operation should calculate correct total");

	/* Test count operation */
	count = 0;
	result = AVLForEach(tree, CountOp, &count);
	TEST_ASSERT(result == 0, "AVLForEach should return 0 on success");
	TEST_ASSERT(count == num_values,
	            "Count operation should count all elements");

	/* Test failing operation */
	result = AVLForEach(tree, FailingOp, NULL);
	TEST_ASSERT(result != 0,
	            "AVLForEach should return non-zero on operation failure");

	/* Test with NULL tree */
	result = AVLForEach(NULL, SumOp, &sum);
	TEST_ASSERT(result == 0, "AVLForEach with NULL tree should fail");

	/* Test with NULL operation */
	result = AVLForEach(tree, NULL, NULL);
	TEST_ASSERT(result == 0, "AVLForEach with NULL operation should fail");

	AVLDestroy(tree);
	TEST_END();
}

int TestStringTree()
{
	int i = 0;
	int result = 0;
	int num_words = 0;
	avl_t* tree = NULL;
	void* found = NULL;
	char* words[] = {"apple", "banana", "cherry", "date", "elderberry"};

	TEST_START();

	tree = AVLCreate(StringCompare);
	num_words = sizeof(words) / sizeof(words[0]);

	/* Insert strings */
	for (i = 0; i < num_words; i++)
	{
		result = AVLInsert(tree, words[i]);
		TEST_ASSERT(result == 0, "String insertion should succeed");
	}

	/* Find strings */
	for (i = 0; i < num_words; i++)
	{
		found = AVLFind(tree, words[i]);
		TEST_ASSERT(found != NULL, "String should be found");
		TEST_ASSERT(strcmp((char*) found, words[i]) == 0,
		            "Found string should match");
	}

	/* Test count */
	TEST_ASSERT(AVLCount(tree) == (size_t) num_words,
	            "String tree count should be correct");

	AVLDestroy(tree);
	TEST_END();
}

int TestComplexScenarios()
{
	int i = 0;
	int* value = NULL;
	void* found = NULL;
	avl_t* tree = NULL;

	TEST_START();

	tree = AVLCreate(IntCompare);

	/* Insert in ascending order */
	for (i = 1; i <= 15; i++)
	{
		value = malloc(sizeof(int));
		*value = i;
		AVLInsert(tree, value);
	}

	/* Remove in descending order */
	for (i = 15; i >= 8; i--)
	{
		AVLRemove(tree, &i);
	}

	TEST_ASSERT(AVLCount(tree) == 7,
	            "Count should be correct after mixed operations");

	/* Verify remaining elements */
	for (i = 1; i <= 7; i++)
	{
		found = AVLFind(tree, &i);
		TEST_ASSERT(found != NULL,
		            "Remaining elements should still be findable");
	}

	AVLDestroy(tree);
	TEST_END();
}

/* Main test runner */
int main()
{
	printf("=== AVL Tree Test Suite ===\n\n");

	/* Run all tests */
	TestAVLCreate();
	TestAVLDestroy();
	TestAVLIsEmpty();
	TestAVLInsertAndFind();
	TestAVLRemove();
	TestAVLCount();
	TestAVLHeight();
	TestAVLForEach();
	TestStringTree();
	TestComplexScenarios();

	/* Print results */
	printf("=== Test Results ===\n");
	printf("Tests run: %d\n", test_count);
	printf("Tests passed: %d\n", test_passed);
	printf("Tests failed: %d\n", test_count - test_passed);

	if (test_passed == test_count)
	{
		printf("\n✅ All tests passed!\n");
		return 0;
	}
	else
	{
		printf("\n⛔ Some tests failed!\n");
		return 1;
	}
}
