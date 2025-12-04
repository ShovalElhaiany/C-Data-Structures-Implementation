/*****************************************
 * date: Tue Jun 03 2025                 *
 * name: Shoval Elhaiany                 *
 * code reviewer: Ofir Cohen             *
 *****************************************/

#ifndef STACK_H
#define STACK_H

#include <stddef.h> /* size_t */

typedef struct stack stack_t;

/*initialize the stack*/
stack_t* StackCreate(size_t element_size, size_t capacity);

/*deallocate the stack and dereference pointers*/
void StackDestroy(stack_t* stack);

/*push element to the stack*/
void StackPush(stack_t* stack, const void* element);

/*pop last element */
void StackPop(stack_t* stack);

/*return the value of the last element*/
void* StackPeek(stack_t* stack);

/*return the number of elements in the stack*/
size_t StackSize(stack_t* stack);

/*return true if the stack is empty, otherwise return false*/
int StackIsEmpty(stack_t* stack);

/*return the number of elements the stack is capable of holding*/
size_t StackCapacity(stack_t* stack);

#endif /*STACK_H*/
