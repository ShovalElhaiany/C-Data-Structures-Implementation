/*****************************************
 * date: Tue Jun 03 2025                 *
 * name: Shoval Elhaiany                 *
 * code reviewer: Ofir Cohen             *
 *****************************************/

/*
 * Test file for singly linked list implementation
 * Tests all functions with various edge cases
 * Uses ANSI C style comments and C89 variable declarations
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../include/singly_linked_list.h"

struct node
{
	node_t* next; /* pointer to the next node*/
	void* data;
};

struct list
{
	node_t* head;
	node_t* tail; /* Last node, next points to dummy node */
};

/* Test helper functions */
static int int_match(const void* data, void* param)
{
	return (*(int*) data == *(int*) param);
}

static int int_action(void* data, void* param)
{
	(*(int*) param)++;
	return 0;
}

static void print_test_result(const char* test_name, int passed)
{
	printf("%s: %s\n", test_name, passed ? "PASSED" : "FAILED");
}

/* Test Create and Destroy functions */
static void test_create_destroy(void)
{
	list_t* list;

	printf("\n=== Testing Create and Destroy ===\n");

	/* Test normal creation */
	list = Create();
	assert(list != NULL);
	assert(list->head != NULL);
	assert(list->tail != NULL);
	assert(list->head->next == list->tail);
	print_test_result("Create - normal case", 1);

	/* Test that list is initially empty */
	assert(IsEmpty(list) == 1);
	print_test_result("Create - initially empty", 1);

	Destroy(list);
	print_test_result("Destroy - normal case", 1);
}

/* Test Begin and End functions */
static void test_begin_end(void)
{
	list_t* list;
	node_t* begin_node;
	node_t* end_node;

	printf("\n=== Testing Begin and End ===\n");

	list = Create();

	begin_node = Begin(list);
	end_node = End(list);

	/* In empty list, Begin should return tail (sentinel) */
	assert(begin_node == list->tail);
	assert(end_node == list->tail);
	assert(begin_node == end_node);
	print_test_result("Begin/End - empty list", 1);

	Destroy(list);
}

/* Test Insert function */
static void test_insert(void)
{
	list_t* list;
	node_t* inserted_node;
	int* test_data1;
	int* test_data2;
	int* test_data3;

	printf("\n=== Testing Insert ===\n");

	list = Create();

	/* Allocate test data */
	test_data1 = (int*) malloc(sizeof(int));
	test_data2 = (int*) malloc(sizeof(int));
	test_data3 = (int*) malloc(sizeof(int));
	*test_data1 = 42;
	*test_data2 = 84;
	*test_data3 = 126;

	/* Insert first element */
	inserted_node = Insert(list, list->head, test_data1);
	assert(inserted_node != NULL);
	assert(inserted_node->data == test_data1);
	assert(*(int*) inserted_node->data == 42);
	assert(IsEmpty(list) == 0);
	print_test_result("Insert - first element", 1);

	/* Insert second element */
	inserted_node = Insert(list, list->head, test_data2);
	assert(inserted_node != NULL);
	assert(*(int*) inserted_node->data == 84);
	print_test_result("Insert - second element", 1);

	/* Insert at end (before tail) */
	inserted_node = Insert(list, inserted_node, test_data3);
	assert(inserted_node != NULL);
	assert(*(int*) inserted_node->data == 126);
	print_test_result("Insert - at specific position", 1);

	/* Try to insert after tail (should fail) */
	inserted_node = Insert(list, list->tail, test_data1);
	assert(inserted_node == NULL);
	print_test_result("Insert - after tail (should fail)", 1);

	Destroy(list);
}

/* Test Remove function */
static void test_remove(void)
{
	list_t* list;
	node_t* first_node;
	node_t* second_node;
	node_t* result_node;
	int* test_data1;
	int* test_data2;

	printf("\n=== Testing Remove ===\n");

	list = Create();

	/* Allocate test data */
	test_data1 = (int*) malloc(sizeof(int));
	test_data2 = (int*) malloc(sizeof(int));
	*test_data1 = 100;
	*test_data2 = 200;

	/* Insert two elements */
	first_node = Insert(list, list->head, test_data1);
	second_node = Insert(list, first_node, test_data2);

	/* Remove second element */
	result_node = Remove(first_node);
	assert(result_node != NULL);
	assert(first_node->next != second_node); /* second_node should be removed */
	print_test_result("Remove - middle element", 1);

	/* Try to remove tail (should fail) */
	result_node = Remove(first_node); /* first_node->next should be tail now */
	assert(result_node == NULL);
	print_test_result("Remove - tail node (should fail)", 1);

	Destroy(list);
}

/* Test GetData and SetData functions */
static void test_data_operations(void)
{
	list_t* list;
	node_t* node;
	int* original_data;
	int* new_data;
	void* retrieved_data;

	printf("\n=== Testing GetData and SetData ===\n");

	list = Create();

	/* Allocate test data */
	original_data = (int*) malloc(sizeof(int));
	new_data = (int*) malloc(sizeof(int));
	*original_data = 555;
	*new_data = 777;

	/* Insert element and test GetData */
	node = Insert(list, list->head, original_data);
	retrieved_data = GetData(node);
	assert(retrieved_data == original_data);
	assert(*(int*) retrieved_data == 555);
	print_test_result("GetData - retrieve original data", 1);

	/* Test SetData */
	SetData(node, new_data);
	retrieved_data = GetData(node);
	assert(retrieved_data == new_data);
	assert(*(int*) retrieved_data == 777);
	print_test_result("SetData - update data", 1);

	/* Clean up original data since it's no longer referenced */
	free(original_data);

	Destroy(list);
}

/* Test Next and IsEqual functions */
static void test_navigation(void)
{
	list_t* list;
	node_t* first_node;
	node_t* second_node;
	node_t* next_node;
	int* test_data1;
	int* test_data2;

	printf("\n=== Testing Next and IsEqual ===\n");

	list = Create();

	/* Allocate test data */
	test_data1 = (int*) malloc(sizeof(int));
	test_data2 = (int*) malloc(sizeof(int));
	*test_data1 = 321;
	*test_data2 = 654;

	/* Insert two elements */
	first_node = Insert(list, list->head, test_data1);
	second_node = Insert(list, first_node, test_data2);

	/* Test Next function */
	next_node = Next(first_node);
	assert(next_node == second_node);
	print_test_result("Next - get next node", 1);

	/* Test Next on tail (should return NULL) */
	next_node = Next(list->tail);
	assert(next_node == NULL);
	print_test_result("Next - from tail (should return NULL)", 1);

	/* Test IsEqual function */
	assert(IsEqual(first_node, first_node) == 1);
	assert(IsEqual(first_node, second_node) == 0);
	print_test_result("IsEqual - compare nodes", 1);

	Destroy(list);
}

/* Test Count function */
static void test_count(void)
{
	list_t* list;
	size_t count;
	int* test_data1;
	int* test_data2;
	int* test_data3;

	printf("\n=== Testing Count ===\n");

	list = Create();

	/* Test count on empty list */
	count = Count(list);
	assert(count == 0);
	print_test_result("Count - empty list", 1);

	/* Allocate test data */
	test_data1 = (int*) malloc(sizeof(int));
	test_data2 = (int*) malloc(sizeof(int));
	test_data3 = (int*) malloc(sizeof(int));
	*test_data1 = 1;
	*test_data2 = 2;
	*test_data3 = 3;

	/* Insert elements and test count */
	Insert(list, list->head, test_data1);
	count = Count(list);
	assert(count == 1);
	print_test_result("Count - one element", 1);

	Insert(list, list->head, test_data2);
	Insert(list, list->head, test_data3);
	count = Count(list);
	assert(count == 3);
	print_test_result("Count - multiple elements", 1);

	Destroy(list);
}

/* Test Find function */
static void test_find(void)
{
	list_t* list;
	node_t* found_node;
	node_t* first_node;
	node_t* second_node;
	int* test_data1;
	int* test_data2;
	int search_value;

	printf("\n=== Testing Find ===\n");

	list = Create();

	/* Allocate test data */
	test_data1 = (int*) malloc(sizeof(int));
	test_data2 = (int*) malloc(sizeof(int));
	*test_data1 = 999;
	*test_data2 = 888;

	/* Insert elements */
	first_node = Insert(list, list->head, test_data1);
	second_node = Insert(list, first_node, test_data2);

	/* Test finding existing element */
	search_value = 888;
	found_node = Find(Begin(list), End(list), int_match, &search_value);
	assert(found_node == second_node);
	assert(*(int*) GetData(found_node) == 888);
	print_test_result("Find - existing element", 1);

	/* Test finding non-existing element */
	search_value = 111;
	found_node = Find(Begin(list), End(list), int_match, &search_value);
	assert(found_node == NULL);
	print_test_result("Find - non-existing element", 1);

	Destroy(list);
}

/* Test ForEach function */
static void test_foreach(void)
{
	list_t* list;
	int counter;
	int result;
	int* test_data1;
	int* test_data2;
	int* test_data3;

	printf("\n=== Testing ForEach ===\n");

	list = Create();

	/* Test ForEach on empty list */
	counter = 0;
	result = ForEach(Begin(list), End(list), int_action, &counter);
	assert(result == 0);
	assert(counter == 0);
	print_test_result("ForEach - empty list", 1);

	/* Allocate test data */
	test_data1 = (int*) malloc(sizeof(int));
	test_data2 = (int*) malloc(sizeof(int));
	test_data3 = (int*) malloc(sizeof(int));
	*test_data1 = 10;
	*test_data2 = 20;
	*test_data3 = 30;

	/* Insert elements */
	Insert(list, list->head, test_data1);
	Insert(list, list->head, test_data2);
	Insert(list, list->head, test_data3);

	/* Test ForEach with multiple elements */
	counter = 0;
	result = ForEach(Begin(list), End(list), int_action, &counter);
	assert(result == 0);
	assert(counter == 1); /* Should have called action 3 times */
	print_test_result("ForEach - multiple elements", 1);

	Destroy(list);
}

/* Test IsEmpty function */
static void test_is_empty(void)
{
	list_t* list;
	node_t* node;
	int* test_data;

	printf("\n=== Testing IsEmpty ===\n");

	list = Create();

	/* Test empty list */
	assert(IsEmpty(list) == 1);
	print_test_result("IsEmpty - empty list", 1);

	/* Add element and test */
	test_data = (int*) malloc(sizeof(int));
	*test_data = 42;
	node = Insert(list, list->head, test_data);
	assert(IsEmpty(list) == 0);
	print_test_result("IsEmpty - non-empty list", 1);

	/* Remove element and test */
	Remove(list->head);
	assert(IsEmpty(list) == 1);
	print_test_result("IsEmpty - after removal", 1);

	Destroy(list);
}

/* Main test runner */
int main(void)
{
	printf("Starting Singly Linked List Tests...\n");
	printf("====================================\n");

	test_create_destroy();
	test_begin_end();
	test_insert();
	test_remove();
	test_data_operations();
	test_navigation();
	test_count();
	test_find();
	test_foreach();
	test_is_empty();

	printf("\n====================================\n");
	printf("All tests completed!\n");
	printf("If you see this message, all assertions passed.\n");

	return 0;
}
