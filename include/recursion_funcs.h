/*****************************************
 * date: Mon Jun 09 2025                 *
 * name: Shoval Elhaiany                 *
 * code reviewer: Nadav Shimoni          *
 *****************************************/

#ifndef RECURSION_FUNCS_H
#define RECURSION_FUNCS_H

/* Include linked list implementation for recursive list operations */
#include "../include/singly_linked_list.h"

/* Include stack implementation for sorting and insertion functions */
#include "../include/stack.h"

#include <stddef.h> /* size_t */

/* Compute Fibonacci number iteratively for given index */
int Fibonacci(int element_index);

/* Compute Fibonacci number recursively for given index */
int RecursiveFibonacci(int element_index);

/* Reverse a singly linked list recursively and return new head */
node_t* FlipList(node_t* node);

/* Sort the entire stack using recursive insertion */
void StackSort(stack_t* stack);

/* Calculate string length recursively */
size_t StrLen(const char* str);

/* Compare two strings recursively */
int StrCmp(const char* str1, const char* str2);

/* Copy source string into destination recursively */
char* StrCpy(char* dest, const char* src);

/* Concatenate source string to destination recursively */
char* StrCat(char* dest, const char* src);

/* Find substring within string recursively */
char* StrStr(const char* str, const char* substring);

#endif /* RECURSION_FUNCS_H */
