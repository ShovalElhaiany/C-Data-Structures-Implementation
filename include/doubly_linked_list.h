#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stddef.h> /* size_t */

typedef struct list list_t;
typedef struct node node_t;

typedef int (*action_func_t)(void* data, void* param);
typedef int (*match_func_t)(const void* data, void* param);

/* Creates an empty list and returns it.
   Returns NULL upon failure.
   Call Destroy when done working with the list. */
list_t* create();

/* Destroys the list.
   Call when done working with the list.
   Time Complexity: O(n)
   Note: It is legal to destroy NULL.*/
void destroy(list_t* list);

/* Returns an iterator to the first element.
   If the list is empty returns End.
   Time Complexity: O(1) */
node_t* begin(const list_t* list);

/* Returns an iterator to beyond the last element (out of range).
   Time Complexity: O(1) */
node_t* end(const list_t* list);

/* Returns an iterator to the element following cur.
   Do not use or go beyond SListEnd().
   Time Complexity: O(1) */
node_t* next(node_t* node);

/* Returns an iterator to the element prev cur.
   Do not use or go beyond SListEnd().
   Time Complexity: O(1) */
node_t* prev(node_t* node);

/* Returns true if both iterators refer to the same element. */
int isequal(node_t* node1, node_t* node2);

/* Returns the data from the element referred to by iter. */
void* getdata(node_t* node);

/* Sets the data in the node referred to by iter. */
void setdata(node_t* node, void* data);

/* Inserts data as a new element, to before the element referred to by cur.
   Returns an iterator to the new element, or SListEnd(list) upon failure.
   Time Complexity: O(1) */
node_t* insert(list_t* list, node_t* node, void* data);

/* Removes the node referred to by cur.
   O(1) */
void removelist(node_t* node);

/* Returns 1 if the list is empty, 0 if it's not.
   Time Complexity: O(1) */
int isempty(const list_t* list);

/* Returns the number of elements in the list.
   Time Complexity: O(n) */
size_t count(const list_t* list);

/* In the range between begin and end, find and return the first element
   whose data matches param when compared using the is_match_func function.
   The is_match_func function should return 1 if the data matches.
   Returns the first element that matches, or to if not found.
   O(n) */
node_t* find(node_t* from, node_t* to, match_func_t is_match_func, void* param);

/* Sends the data from each element in the list (in order) to the
   function action_func, along with params. Stops if action_func
   fails (return != 0), even if not all elements have been sent.
   Returns the value returned from the last call to action_func.
   Time Complexity: O(n) */
int foreach (node_t* from, node_t * to, action_func_t action_func,
             void* params);

#endif /* DOUBLY_LINKED_LIST_H */
