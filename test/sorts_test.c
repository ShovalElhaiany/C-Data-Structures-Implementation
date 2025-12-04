/*****************************************
 * date: Wed Jun 11 2025                 *
 * name: Shoval Elhaiany                 *
 * code reviewer: Nadav Shimoni          *
 *****************************************/

#include "../include/sorts.h"

#include <assert.h> /* assert */
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, free, rand, qsort */
#include <time.h>   /* clock_t, clock, CLOCKS_PER_SEC */

/* ============================== HELPER FUNCS ============================== */

/* Comparison function for integers */
static int IntCmp(const void* data1, const void* data2)
{
	int data1_val = *(int*) data1;
	int data2_val = *(int*) data2;

	if (data1_val > data2_val)
		return 1;
	if (data1_val < data2_val)
		return -1;
	else
		return 0;
}

static void PrintRuntime(char* func_name, func_t func)
{
	clock_t begin = clock();
	clock_t end;
	double time_spent;

	func();

	end = clock();
	time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
	printf("%s runtime: %.6f\n", func_name, time_spent);
}

/* ============================== SORTS TESTS ============================== */

void BinarySearchTests(void)
{
	int target1 = 5;
	int target2 = 0;

	int arr[] = {3, 4, 5, 6, 7};
	size_t size = sizeof(arr) / sizeof(int);

	int index1 = IterativeBinarySearch(arr, target1, size);
	int index2 = RecursiveBinarySearch(arr, target1, 0, size - 1);

	assert(index1 == 2);
	assert(index2 == 2);

	index1 = IterativeBinarySearch(arr, target2, size);
	index2 = RecursiveBinarySearch(arr, target2, 0, size - 1);

	assert(index1 == -1);
	assert(index2 == -1);

	printf("BinarySearch: PASS\n");
}

void BubbleSortTest(void)
{
	int i = 0;
	int* arr = (int*) malloc(ARRAY_SIZE * sizeof(int));
	if (!arr)
		return;

	for (i = 0; i < ARRAY_SIZE; i++)
		arr[i] = rand() % 100;

	BubbleSort(arr, ARRAY_SIZE);

	for (i = 1; i < ARRAY_SIZE; i++)
		assert(arr[i - 1] <= arr[i]);

	printf("BubbleSort: PASS\n");
	free(arr);
}

void CountingSortTest(void)
{
	int i = 0;
	int* arr = (int*) malloc(ARRAY_SIZE * sizeof(int));
	if (!arr)
		return;

	for (i = 0; i < ARRAY_SIZE; i++)
		arr[i] = rand() % 100;

	CountingSort(arr, ARRAY_SIZE);

	for (i = 1; i < ARRAY_SIZE; i++)
		assert(arr[i - 1] <= arr[i]);

	printf("CountingSort: PASS\n");
	free(arr);
}

void QuickSortTest(void)
{
	int i = 0;
	int low = 0;
	int high = ARRAY_SIZE - 1;
	int* arr = (int*) malloc(ARRAY_SIZE * sizeof(int));
	if (!arr)
		return;

	for (i = 0; i < ARRAY_SIZE; i++)
		arr[i] = rand() % 100;

	QuickSort(arr, low, high, sizeof(int), IntCmp);

	for (i = 1; i < ARRAY_SIZE; i++)
		assert(arr[i - 1] <= arr[i]);

	printf("QuickSort: PASS\n");
	free(arr);
}

void SelectionSortTest(void)
{
	int i = 0;
	int* arr = (int*) malloc(ARRAY_SIZE * sizeof(int));
	if (!arr)
		return;

	for (i = 0; i < ARRAY_SIZE; i++)
		arr[i] = rand() % 100;

	SelectionSort(arr, ARRAY_SIZE);

	for (i = 1; i < ARRAY_SIZE; i++)
		assert(arr[i - 1] <= arr[i]);

	printf("SelectionSort: PASS\n");
	free(arr);
}

void InsertionSortTest(void)
{
	int i = 0;
	int* arr = (int*) malloc(ARRAY_SIZE * sizeof(int));
	if (!arr)
		return;

	for (i = 0; i < ARRAY_SIZE; i++)
		arr[i] = rand() % 100;

	InsertionSort(arr, ARRAY_SIZE);

	for (i = 1; i < ARRAY_SIZE; i++)
		assert(arr[i - 1] <= arr[i]);

	printf("InsertionSortTest: PASS\n");
	free(arr);
}

/* ================================== MAIN ================================== */

int main(void)
{
	printf("\n========== RECURSION TESTS ==========\n\n");

	BinarySearchTests();
	BubbleSortTest();
	CountingSortTest();
	QuickSortTest();

	printf("\n========== ALL TESTS PASSED! ==========\n\n");

	printf("\n========== RUNTIME CHECKS ==========\n\n");

	PrintRuntime("BubbleSort", BubbleSortTest);
	PrintRuntime("CountingSort", CountingSortTest);
	PrintRuntime("QuickSort", QuickSortTest);
	PrintRuntime("qsort", (func_t) qsort);

	printf("\n========== Advanced ==========\n\n");

	SelectionSortTest();
	PrintRuntime("SelectionSort", SelectionSortTest);
	InsertionSortTest();
	PrintRuntime("SelectionSort", InsertionSortTest);

	return 0;
}
