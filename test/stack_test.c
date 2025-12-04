/*****************************************
 * date: Tue Jun 03 2025                 *
 * name: Shoval Elhaiany                 *
 * code reviewer: Ofir Cohen             *
 *****************************************/

#include <stdio.h> /* printf */
#include "../include/stack.h"

int main()
{
	int i = 0;
	char* top;
	stack_t* stack;
	int num = 5;
	size_t capacity = 10;

	stack = StackCreate(sizeof(char), capacity);

	if (stack == NULL)
	{
		printf("Failed to create stack\n");
		return 1;
	}

	printf("Pushing elements into the stack:\n");

	for (i = 0; i < (int) capacity; i++)
	{
		StackPush(stack, &num);
		top = StackPeek(stack);
		if (top != NULL)
		{
			printf("Pushed: %d | Top: %d | Size: %lu\n", num, *top,
			       StackSize(stack));
		}
	}

	printf("\nPopping all elements:\n");
	while (!StackIsEmpty(stack))
	{
		top = StackPeek(stack);
		if (top != NULL)
		{
			printf("Peeked: %d \n", *top);
		}

		StackPop(stack);
		printf("Popped | New size: %lu\n", StackSize(stack));
	}

	StackDestroy(stack);
	return 0;
}
