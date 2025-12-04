/*****************************************
 * date: Mon Jun 09 2025                 *
 * name: Shoval Elhaiany                 *
 * code reviewer: Nadav Shimoni          *
 *****************************************/

#include "../include/recursion_funcs.h"

#include "../src/stack.c"
#include "../src/singly_linked_list.c"

#include <assert.h> /* assert */
#include <string.h> /* strncmp, strlen */

/* ============================ FIBONACCI FUNCS ============================ */

int Fibonacci(int element_index)
{
	int i = 0;
	int temp = 0;
	int num1 = 0;
	int num2 = 1;

	assert(0 <= element_index);

	for (i = 1; i < element_index; ++i)
	{
		temp = num1 + num2;
		num1 = num2;
		num2 = temp;
	}

	return (0 == element_index) ? 0 : num2;
}

int RecursiveFibonacci(int element_index)
{
	if (element_index <= 1)
	{
		return element_index;
	}
	return RecursiveFibonacci(element_index - 1) +
	       RecursiveFibonacci(element_index - 2);
}

/* =============================== FLIP LIST =============================== */

node_t* FlipList(node_t* node)
{
	if (node->next == NULL)
		return node;

	node_t* temp = FlipList(node->next);

	node->next->next = node;
	node->next = NULL;

	return temp;
}

/* ================================= STACK ================================= */

static void SortedInsert(stack_t* stack, const void* element)
{
	if (StackIsEmpty(stack) || (*(int*) element > *(int*) StackPeek(stack)))
	{
		StackPush(stack, element);
	}
	else
	{
		void* temp = malloc(stack->element_size);
		if (!temp)
			return;
		memcpy(temp, StackPeek(stack), stack->element_size);
		StackPop(stack);
		SortedInsert(stack, element);
		StackPush(stack, temp);
		free(temp);
	}
}

void StackSort(stack_t* stack)
{
	if (!StackIsEmpty(stack))
	{
		void* element = malloc(stack->element_size);
		if (!element)
			return;
		memcpy(element, StackPeek(stack), stack->element_size);
		StackPop(stack);
		StackSort(stack);
		SortedInsert(stack, element);
		free(element);
	}
}
/* ============================== STRINGS LIST ============================== */

size_t StrLen(const char* str)
{
	return *str ? 1 + StrLen(str + 1) : 0;
}

int StrCmp(const char* str1, const char* str2)
{
	return *str1 && *str1 == *str2
	           ? StrCmp(str1 + 1, str2 + 1)
	           : *(unsigned char*) str1 - *(unsigned char*) str2;
}

char* StrCpy(char* dest, const char* src)
{
	*dest = *src;
	if (*src)
		StrCpy(dest + 1, src + 1);
	return dest;
}

char* StrCat(char* dest, const char* src)
{
	if (*dest)
		StrCat(dest + 1, src);
	else
		StrCpy(dest, src);
	return dest;
}

char* StrStr(const char* str, const char* substring)
{
	if (!*substring)
		return (char*) str;
	if ('\0' == *str)
		return NULL;
	if (strncmp(str, substring, strlen(substring)) == 0)
		return (char*) str;
	return StrStr(str + 1, substring);
}
