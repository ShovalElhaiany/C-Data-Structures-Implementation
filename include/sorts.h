/*****************************************
 * date: Wed Jun 11 2025                 *
 * name: Shoval Elhaiany                 *
 * code reviewer: Nadav Shimoni          *
 *****************************************/

#ifndef SORTS_H
#define SORTS_H

#include <stddef.h> /* size_t */

#define ARRAY_SIZE 5000

/* Comparison function typedef */
typedef int (*cmp_func_t)(const void* data1, const void* data2);

typedef void (*func_t)(void);

/* =========================== BINARY SEARCH =========================== */

/**
 * Performs an iterative binary search on a sorted integer array.
 * Index of target if found, otherwise -1.
 **/
int IterativeBinarySearch(int* arr, int target, size_t size);

/**
 * Performs a recursive binary search on a sorted integer array.
 * return Index of target if found, otherwise -1.
 **/
int RecursiveBinarySearch(int* arr, int target, int low, int high);

/* ================================= SORTS ================================= */

/* Sorts an integer array using bubble sort. */
void BubbleSort(int* arr, size_t size);

/* Sorts an integer array using counting sort. */
void CountingSort(int* arr, size_t size);

/* Sorts an array using quicksort with a generic comparator. */
void QuickSort(void* arr, int low, int high, size_t block_size,
               cmp_func_t cmp_func);

/* ================================ ADVANCED ================================ */

void SelectionSort(int* arr, size_t size);

void InsertionSort(int* arr, size_t size);

#endif /* SORTS_H */
