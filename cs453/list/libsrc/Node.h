#ifndef __NODE_H
#define __NODE_H

#include <stdio.h>
#include <stdlib.h>
#include "common.h"

typedef struct node Node;
typedef struct node *NodePtr;

struct node {
    void *obj;
    NodePtr next;
    NodePtr prev;
};

/**
 * Allocates a new Node object and initializes it.
 *
 * @return a pointer to the allocated Node.
 */
NodePtr createNode(const void *data);

/**
 * Frees all elements of the given Node.
 * Does nothing if Node is NULL.
 *
 * @param node a pointer to a Node.
 */
void freeNode(const NodePtr node, void (*freeObject) (const void *));


#endif				/* __NODE_H */
