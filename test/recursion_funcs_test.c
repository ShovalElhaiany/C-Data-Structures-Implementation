/*****************************************
 * date: Mon Jun 09 2025                 *
 * name: Shoval Elhaiany                 *
 * code reviewer: Nadav Shimoni          *
 *****************************************/

#include "../src/recursion_funcs.c"

#include <assert.h> /* assert */
#include <string.h> /* strcmp */
#include <stdio.h>  /* printf */

/* ============================ RECURSION TESTS ============================ */

static void FibonacciTest(void)
{
	int index = 10;

	int result1 = Fibonacci(index);
	int result2 = RecursiveFibonacci(index);

	assert(result1 == 55);
	assert(result2 == 55);

	printf("Fibonacci: PASS\n");
}

static void FlipListTest(void)
{
	list_t* list = Create();
	int data1 = 1, data2 = 2, data3 = 3;

	node_t* node1 = Insert(list, list->head, &data1);
	node_t* node2 = Insert(list, node1, &data2);
	node_t* node3 = Insert(list, node2, &data3);

	node_t* flipped_list = FlipList(Begin(list));
	node_t* curr = Next(flipped_list);

	assert(*(int*) GetData(curr) == 3);
	assert(*(int*) GetData(curr->next) == 2);
	assert(*(int*) GetData(curr->next->next) == 1);

	printf("FlipListTest: PASS\n");
	Destroy(list);
}

static void StackSortTest(void)
{
	size_t i = 0;
	size_t capacity = 5;
	int arr[] = {20, 55, 1, 8, 10};

	stack_t* stack = StackCreate(sizeof(int), capacity);

	for (i = 0; i < capacity; i++)
	{
		StackPush(stack, &arr[i]);
	}

	StackSort(stack);
	assert(*(int*) StackPeek(stack) == 55);
	StackPop(stack);
	assert(*(int*) StackPeek(stack) == 20);
	StackPop(stack);
	assert(*(int*) StackPeek(stack) == 10);
	StackPop(stack);
	assert(*(int*) StackPeek(stack) == 8);
	StackPop(stack);
	assert(*(int*) StackPeek(stack) == 1);

	printf("StackSortTest: PASS\n");
	StackDestroy(stack);
}

static void StrlenTest(void)
{
	assert(StrLen("hello") == 5);
	assert(StrLen("") == 0);
	printf("StrlenTest: PASS\n");
}

static void StrcmpTest(void)
{
	assert(StrCmp("abc", "abc") == 0);
	assert(StrCmp("abc", "abd") < 0);
	assert(StrCmp("abd", "abc") > 0);
	printf("StrcmpTest: PASS\n");
}

static void StrcpyTest(void)
{
	char dest[16];
	StrCpy(dest, "test");
	assert(strcmp(dest, "test") == 0);
	printf("StrcpyTest: PASS\n");
}

static void StrcatTest(void)
{
	char dest[11] = "hello";
	StrCat(dest, " world");
	assert(strcmp(dest, "hello world") == 0);
	printf("StrcatTest: PASS\n");
}

static void StrstrTest(void)
{
	char str1[] = "hello world";
	assert(StrStr(str1, "world") == str1 + 6);
	char str2[] = "hello";
	assert(StrStr(str2, "lo") == str2 + 3);
	char str3[] = "hello";
	assert(StrStr(str3, "") == str3);
	char str4[] = "hello";
	assert(StrStr(str4, "z") == NULL);
	printf("StrstrTest: PASS\n");
}
/* ================================== MAIN ================================== */

int main(void)
{
	printf("\n========== RECURSION TESTS ==========\n\n");

	FibonacciTest();
	FlipListTest();
	StackSortTest();
	StrlenTest();
	StrcmpTest();
	StrcpyTest();
	StrcatTest();
	StrstrTest();

	printf("\n========== ALL TESTS PASSED! ==========\n\n");

	return 0;
}
