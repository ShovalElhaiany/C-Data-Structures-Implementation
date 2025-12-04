
#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc, free */
#include "doubly_linked_list.h"

struct node
{
	node_t* next; /* pointer to the next node*/
	node_t* prev; /* pointer to the prev node*/
	void* data;
};

struct list
{
	node_t* head;
	node_t* tail; /* Last node, next points to dummy node */
};

static int counthandler(void* data, void* count);

/********************************* API FUNCS *********************************/

list_t* create()
{
	list_t* list = (list_t*) malloc(sizeof(list_t));
	if (!list)
	{
		return NULL;
	}

	node_t* head = (node_t*) malloc(sizeof(node_t));
	if (!head)
	{
		free(list);
		return NULL;
	}

	node_t* tail = (node_t*) malloc(sizeof(node_t));
	if (!tail)
	{
		free(head);
		free(list);
		return NULL;
	}

	head->next = tail;
	head->prev = NULL;
	head->data = NULL;

	tail->next = NULL;
	tail->prev = head;
	tail->data = NULL;

	list->head = head;
	list->tail = tail;

	return list;
}

void destroy(list_t* list)
{
	if (list)
	{
		node_t* ptr = list->head;
		while (ptr)
		{
			node_t* next = ptr->next;
			free(ptr);
			ptr = next;
		}
		free(list);
	}
}

node_t* begin(const list_t* list)
{
	if (list)
	{
		return list->head;
	}
	return NULL;
}

node_t* end(const list_t* list)
{
	if (list)
	{
		return list->tail;
	}
	return NULL;
}

node_t* next(node_t* node)
{
	if (node)
	{
		return node->next;
	}
	return NULL;
}

node_t* prev(node_t* node)
{
	if (node)
	{
		return node->prev;
	}
	return NULL;
}

int isequal(node_t* node1, node_t* node2)
{
	if (node1 && node2)
	{
		return node1 == node2;
	}
}

void* getdata(node_t* node)
{
	if (node && node->data)
	{
		return node->data;
	}
	return NULL;
}

void setdata(node_t* node, void* data)
{
	if (node && data && node->data)
	{
		node->data = data;
	}
}

node_t* insert(list_t* list, node_t* node, void* data)
{
	if (list && node && data)
	{
		node_t* new_node = (node_t*) malloc(sizeof(node_t));
		new_node->data = data;
		new_node->next = node;
		new_node->prev = node->prev;
		if (node->prev)
		{
			node->prev->next = new_node;
		}

		node->prev = new_node;

		return new_node;
	}
	return NULL;
}

void removelist(node_t* node)
{
	if (node && node->next)
	{
		(node->prev)->next = node->next;
		(node->next)->prev = node->prev;

		node_t* next = node->next;

		free(node);
	}
}

int isempty(const list_t* list)
{
	if (list)
	{
		return list->head->next == list->tail;
	}
	return 0;
}

size_t count(const list_t* list)
{
	if (list)
	{
		size_t count = 0;
		foreach (list->head, list->tail, counthandler, &count)
			;

		return count - 1;
	}
}

node_t* find(node_t* from, node_t* to, match_func_t is_match_func, void* param)
{
	if (from && to && is_match_func && param)
	{
		while (from != to && from->data)
		{
			if (is_match_func(from->data, param))
				return from;
			from = from->next;
		}

		return NULL;
	}
}

int foreach (node_t* from, node_t * to, action_func_t action_func, void* params)
{
	if (from && to && action_func && params)
	{
		int result = 0;
		while (from != to)
		{
			result = action_func(from->data, params);
			if (result)
				return 1;
			from = from->next;
		}

		return 0;
	}
}

/******************************* HELPERS FUNCS ********************************/

static int counthandler(void* data, void* count)
{
	(void) data;
	++(*(size_t*) count);
	return 1;
}
