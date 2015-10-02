#include "Node.h"


NodePtr createNode(const void *data)
{
    NodePtr newNode = (NodePtr) malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->prev = NULL;
    newNode->obj = (void *) data;
    return newNode;
}

void freeNode(const NodePtr node, void (*freeObject) (const void *))
{
    if (node == NULL)
	return;
    (*freeObject) (node->obj);
    free(node);
}
