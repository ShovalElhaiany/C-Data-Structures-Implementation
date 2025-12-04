/*****************************************
 * date: Tue Jun 03 2025                 *
 * name: Shoval Elhaiany                 *
 * code reviewer: Ofir Cohen             *
 *****************************************/

#include <stddef.h> /* size_t */
#include <string.h> /* memcpy */
#include <stdlib.h> /* malloc, free */
#include "../include/stack.h"

struct stack
{
	void* data;          /*array of data, stored by value*/
	size_t element_size; /*size of each stack element in bytes*/
	size_t capacity;     /*max number of elements*/
	size_t occupancy;    /*number of occupied elements*/
};

/*initialize the stack*/
stack_t* StackCreate(size_t element_size, size_t capacity)
{
	stack_t* stack = (stack_t*) malloc(sizeof(*stack));

	if (!stack)
	{
		return NULL;
	}

	stack->capacity = capacity;
	stack->element_size = element_size;
	stack->occupancy = 0;
	stack->data = (void*) malloc(element_size * capacity);

	return stack;
}

/*deallocate the stack and dereference pointers*/
void StackDestroy(stack_t* stack)
{
	if (stack)
	{
		free(stack->data);
		free(stack);
	}
}

/*push element to the stack*/
void StackPush(stack_t* stack, const void* element)
{
	if (stack->capacity == stack->occupancy)
		return;
	memcpy((char*) stack->data + (stack->occupancy * stack->element_size),
	       element, stack->element_size);
	stack->occupancy++;
}

/*pop last element */
void StackPop(stack_t* stack)
{
	if (stack->occupancy == 0)
		return;
	stack->occupancy--;
}

/*return the value of the last element*/
void* StackPeek(stack_t* stack)
{
	if (!stack->occupancy)
		return NULL;
	return (char*) stack->data + (stack->occupancy - 1) * stack->element_size;
}

/*return the number of elements in the stack*/
size_t StackSize(stack_t* stack)
{
	return stack->occupancy;
}

/*return true if the stack is empty, otherwise return false*/
int StackIsEmpty(stack_t* stack)
{
	return stack->occupancy == 0;
}

/*return the number of elements the stack is capable of holding*/
size_t StackCapacity(stack_t* stack)
{
	return stack->capacity;
}
