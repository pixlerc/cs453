#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "Object.h"
#include <Node.h>
#include <List.h>


int main(int argc, char **argv)
{
    int i;
    int n;
    NodePtr node;
    ObjectPtr job;
    ListPtr list;

    if (argc != 2) {
	fprintf(stderr, "Usage: %s <list size> \n", argv[0]);
	exit(1);
    }
    n = atoi(argv[1]);

    list = createList(equals, toString, freeObject);
    for (i = 0; i < n; i++) {
	job = createObject(i, "cmd args");
	node = createNode(job);
	addAtRear(list, node);
    }

    printList(list);
    reverseList(list);
    printList(list);
    reverseList(list);
    printList(list);
    reverseList(list);
    printList(list);
    reverseList(list);
    printList(list);

    freeList(list);

    exit(0);
}
