#include <stdio.h>
#include <stdlib.h>
#include "List.h"

ListPtr createList(int (*compareTo) (const void *, const void *),
		   char *(*toString) (const void *),
		   void (*freeObject) (const void *))
{
    ListPtr list;
    list = (ListPtr) malloc(sizeof(List));
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    list->compareTo = compareTo;
    list->toString = toString;
    list->freeObject = freeObject;
    return list;
}

void freeList(const ListPtr list)
{
    if (list == NULL || list->size < 0) {
	return;
    }
    if (list->head == NULL || list->size == 0) {
	free(list);
	return;
    }
    if (list->head->obj == NULL) {
	return;
    }
    if (list->tail != NULL && list->tail->obj == NULL) {
	return;
    }
    if (list->size == 1 && list->head != NULL) {
	freeNode(list->head, list->freeObject);
	free(list);
	return;
    }

    NodePtr temp = list->head;

    while (temp->next != NULL) {
	NodePtr prev = temp;
	temp = temp->next;
	freeNode(prev, list->freeObject);
    }
    freeNode(temp, list->freeObject);
    free(list);
    return;
}

int getSize(const ListPtr list)
{
    if (list == NULL)
	return 0;

    return list->size;
}

Boolean isEmpty(const ListPtr list)
{
    return list->size == 0;
}

void addAtFront(ListPtr list, NodePtr node)
{
    if (list == NULL)
	return;
    if (node == NULL)
	return;

    if (list->head == NULL) {
	list->head = node;
	list->tail = node;
	node->prev = NULL;
	node->next = NULL;
	list->size++;
    } else {
	node->prev = NULL;
	node->next = list->head;
	list->head->prev = node;
	list->head = node;
	list->size++;
    }

    return;
}

void addAtRear(ListPtr list, NodePtr node)
{
    if (list == NULL)
	return;
    if (node == NULL)
	return;

    if (list->tail == NULL) {
	list->head = node;
	list->tail = node;
	node->next = NULL;
	node->prev = NULL;
	list->size++;
    } else {
	node->next = NULL;
	node->prev = list->tail;
	list->tail->next = node;
	list->tail = node;
	list->size++;
    }
    return;
}

NodePtr removeFront(ListPtr list)
{
    NodePtr rval;

    if (list == NULL)
	return NULL;
    if (list->head == NULL)
	return NULL;

    if (list->size == 1) {
	rval = list->head;
	list->head = NULL;
	list->tail = NULL;
	list->size--;
	return rval;
    }
    rval = list->head;
    list->head = list->head->next;
    list->head->prev = NULL;
    rval->next = NULL;
    list->size--;

    return rval;
}

NodePtr removeRear(ListPtr list)
{
    NodePtr rval;

    if (list == NULL)
	return NULL;
    if (list->tail == NULL)
	return NULL;

    if (list->size == 1) {
	rval = list->head;
	list->head = NULL;
	list->tail = NULL;
	list->size--;
	return rval;
    }
    rval = list->tail;
    list->tail = rval->prev;
    rval->prev = NULL;
    list->tail->next = NULL;
    list->size--;
    return rval;
}

NodePtr removeNode(ListPtr list, NodePtr node)
{
    NodePtr rval;

    if (list == NULL)
	return NULL;
    if (node == NULL)
	return NULL;
    if (list->head == NULL)
	return NULL;

    if (node == list->head)
	return removeFront(list);
    if (node == list->tail)
	return removeRear(list);

    if (search(list, node->obj) != NULL) {
	rval = search(list, node->obj);
	rval->prev->next = rval->next;
	rval->next->prev = rval->prev;
	rval->next = NULL;
	rval->prev = NULL;
	list->size--;
	return rval;
    } else
	return NULL;
}

NodePtr search(ListPtr list, const void *key)
{
    NodePtr rval;

    if (list == NULL)
	rval = NULL;
    else if (list->head == NULL)
	rval = NULL;

    rval = list->head;

    while (rval != NULL) {
	if (list->compareTo(key, rval->obj))
	    return rval;
	else
	    rval = rval->next;
    }
    return NULL;
}

void reverseList(ListPtr list)
{
    if (list == NULL)
	return;
    if (list->head == NULL)
	return;
    if (list->head->next == NULL)
	return;

    printf("reverseList\n");
    NodePtr curr = list->head;
    NodePtr temp = NULL;

    for (int i = 0; i < list->size; i++) {
	temp = curr->prev;
	curr->prev = curr->next;
	curr->next = temp;
	curr = curr->prev;
    }
    list->tail = list->head;
    list->head = temp->prev;
}

void printList(ListPtr list)
{
    if (list == NULL)
	return;
    if (list->head == NULL)
	return;

    NodePtr node = list->head;

    while (node != NULL) {
	char *s = (list->toString) (node->obj);
	printf("%s\n", s);
	free(s);
	node = node->next;
    }
}
