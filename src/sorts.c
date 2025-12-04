/*****************************************
 * date: Wed Jun 11 2025                 *
 * name: Shoval Elhaiany                 *
 * code reviewer: Nadav Shimoni          *
 *****************************************/

#include "../include/sorts.h"

#include <assert.h>  /* assert */
#include <stdbool.h> /* true, false */
#include <stdlib.h>  /* malloc, free */
#include <string.h>  /* memcpy */

/* =========================== BINARY SEARCH SORT =========================== */

int IterativeBinarySearch(int* arr, int target, size_t size)
{
	int low = 0;
	int mid = 0;
	int high = size - 1;

	while (low <= high)
	{
		mid = low + (high - low) / 2;

		if (arr[mid] == target)
			return mid;
		if (arr[mid] < target)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return -1;
}

int RecursiveBinarySearch(int* arr, int target, int low, int high)
{
	int mid = 0;

	if (high >= low)
	{
		mid = low + (high - low) / 2;

		if (arr[mid] == target)
			return mid;
		if (arr[mid] > target)
			return RecursiveBinarySearch(arr, low, mid - 1, target);
		else
			return RecursiveBinarySearch(arr, mid + 1, high, target);
	}
	return -1;
}

/* ============================== BUBBLE SORT ============================== */

void BubbleSort(int* arr, size_t size)
{
	int i = 0;
	int j = 0;
	int temp = 0;
	int swapped = false;

	for (i = 0; i < (int) size - 1; i++)
	{
		swapped = false;
		for (j = 0; j < (int) size - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;

				swapped = true;
			}
		}
		if (!swapped)
		{
			break;
		}
	}
}
/* ============================== COUNTING SORT ==============================
 */

void CountingSort(int* arr, size_t size)
{
	int i = 0;
	int max = arr[0];
	int* index_arr;

	for (i = 1; i < (int) size; i++)
		if (arr[i] > max)
			max = arr[i];

	index_arr = calloc(max + 1, sizeof(int));
	if (!index_arr)
		return;

	for (i = 0; i < (int) size; i++)
		index_arr[arr[i]]++;

	for (i = 0; i <= max; i++)
		while (index_arr[i] > 0)
		{
			*arr++ = i;
			index_arr[i]--;
		}
}

/* =============================== QUICK SORT =============================== */

void QuickSort(void* arr, int low, int high, size_t block_size,
               cmp_func_t cmp_func)
{
	char* buffer = (char*) malloc(block_size);
	int curr_index = -1;
	int swap_marker = low - 1;

	if (low >= high)
		return;

	for (curr_index = low; curr_index < high; curr_index++)
	{
		if (0 <= cmp_func((char*) arr + high * block_size,
		                  (char*) arr + curr_index * block_size))
		{
			swap_marker++;
			if (0 < cmp_func((char*) arr + swap_marker * block_size,
			                 (char*) arr + curr_index * block_size))
			{
				memcpy(buffer, (char*) arr + swap_marker * block_size,
				       block_size);
				memcpy((char*) arr + swap_marker * block_size,
				       (char*) arr + curr_index * block_size, block_size);
				memcpy((char*) arr + curr_index * block_size, buffer,
				       block_size);
			}
		}
	}
	memcpy(buffer, (char*) arr + (swap_marker + 1) * block_size, block_size);
	memcpy((char*) arr + (swap_marker + 1) * block_size,
	       (char*) arr + high * block_size, block_size);
	memcpy((char*) arr + high * block_size, buffer, block_size);
	free(buffer);

	QuickSort(arr, low, swap_marker, block_size, cmp_func);
	QuickSort(arr, swap_marker + 1, high, block_size, cmp_func);
}

/* ============================= SELECTION SORT ============================= */

void SelectionSort(int* arr, size_t size)
{
	int temp = 0;
	int min_index = 0;
	int curr_index = 0;
	int swap_marker = 0;

	for (curr_index = 0; curr_index < (int) size - 1; curr_index++)
	{
		min_index = curr_index;
		for (swap_marker = curr_index + 1; swap_marker < (int) size;
		     swap_marker++)
		{
			if (arr[swap_marker] < arr[min_index])
			{
				min_index = swap_marker;
			}
		}
		temp = arr[curr_index];
		arr[curr_index] = arr[min_index];
		arr[min_index] = temp;
	}
}

/* ============================= INSERTION SORT ============================= */

void InsertionSort(int* arr, size_t size)
{
	int temp = 0;
	int curr_index = 0;
	int swap_marker = 0;

	for (curr_index = 0; curr_index < (int) size - 1; curr_index++)
	{
		swap_marker = curr_index;
		while (arr[swap_marker] > arr[swap_marker + 1])
		{
			temp = arr[swap_marker];
			arr[swap_marker] = arr[swap_marker + 1];
			arr[swap_marker + 1] = temp;

			swap_marker--;
		}
	}
}
