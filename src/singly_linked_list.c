/*****************************************
 * date: Tue Jun 03 2025                 *
 * name: Shoval Elhaiany                 *
 * code reviewer: Ofir Cohen             *
 *****************************************/

#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc, free */
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

list_t* Create();
void Destroy(list_t* list);
node_t* Begin(const list_t* list);
node_t* End(const list_t* list);
node_t* Next(node_t* node);
int IsEqual(node_t* node1, node_t* node2);
void* GetData(node_t* node);
void SetData(node_t* node, void* data);
node_t* Insert(list_t* list, node_t* node, void* data);
node_t* Remove(node_t* node);
int IsEmpty(const list_t* list);
size_t Count(const list_t* list);
node_t* Find(node_t* from, node_t* to, match_func_t is_match_func, void* param);
int ForEach(node_t* from, node_t* to, action_func_t action_func, void* param);

static int CountHandler(void* data, void* count);

/********************************* API FUNCS *********************************/

list_t* Create()
{
	list_t* list = (list_t*) malloc(sizeof(list_t));
	if (!list)
	{
		return NULL;
	}

	node_t* head = (node_t*) malloc(sizeof(node_t));
	if (!head)
	{
		return NULL;
	}

	node_t* tail = (node_t*) malloc(sizeof(node_t));
	if (!tail)
	{
		return NULL;
	}

	head->next = tail;
	head->data = NULL;

	tail->next = NULL;
	tail->data = NULL;

	list->head = head;
	list->tail = tail;

	return list;
}

void Destroy(list_t* list)
{
	if (list)
	{
		node_t* ptr = list->head;
		node_t* next = ptr;
		while (ptr)
		{
			next = ptr->next;
			free(ptr);
			ptr = next;
		}
		free(list);
	}
}

node_t* Begin(const list_t* list)
{
	if (list)
	{
		return list->head->next;
	}
}

node_t* End(const list_t* list)
{
	if (list)
	{
		return list->tail;
	}
}

node_t* Next(node_t* node)
{
	if (node && node->next)
	{
		return node->next;
	}
}
int IsEqual(node_t* node1, node_t* node2)
{
	if (node1 && node2)
	{
		return node1 == node2;
	}
}

void* GetData(node_t* node)
{
	if (node && node->data)
	{
		return node->data;
	}
}

void SetData(node_t* node, void* data)
{
	if (node && data && node->data)
	{
		node->data = data;
	}
}

node_t* Insert(list_t* list, node_t* node, void* data)
{
	if (list && node && data && node != list->tail)
	{
		node_t* new_node = (node_t*) malloc(sizeof(node_t));
		new_node->data = data;
		new_node->next = node->next;

		node->next = new_node;

		return new_node;
	}
	return NULL;
}

node_t* Remove(node_t* node)
{
	if (node && node->next)
	{
		node_t* next = node->next;
		free(node);

		return next;
	}

	return NULL;
}

int IsEmpty(const list_t* list)
{
	if (list)
	{
		return list->head->next == list->tail;
	}
	return NULL;
}

size_t Count(const list_t* list)
{
	if (list)
	{
		size_t count = 0;
		ForEach(list->head, list->tail, CountHandler, &count);

		return count - 1;
	}
}

node_t* Find(node_t* from, node_t* to, match_func_t is_match_func, void* param)
{
	if (from && to && is_match_func && param)
	{
		while (from != to)
		{
			if (is_match_func(from->data, param))
				return from;
			from = from->next;
		}

		return NULL;
	}
}

int ForEach(node_t* from, node_t* to, action_func_t action_func, void* param)
{
	if (from && to && action_func && param)
	{
		int result = 0;
		while (from != to)
		{
			result = action_func(from->data, param);
			if (!result)
				return result;
			from = from->next;
		}

		return result;
	}
}

/******************************* HELPERS FUNCS ********************************/

static int CountHandler(void* data, void* count)
{
	(void) data;
	++(*(size_t*) count);
	return 1;
}
