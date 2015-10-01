/*
 * UnitTestList.c
 *
 *      Author: marissa
 */

#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "Object.h"
#include <Node.h>
#include <List.h>

/* 
 * macro to mimic the functionality of assert() from <assert.h>. The difference is that this version doesn't exit the program entirely.
 * It will just break out of the current function (or test case in this context).
 */
#define myassert(expr) if(!(expr)){ fprintf(stderr, "\t[assertion failed] %s: %s\n", __PRETTY_FUNCTION__, __STRING(expr)); return FALSE; }

ListPtr testlist;

int testCount = 0;
int passCount = 0;
/**
 * Prints the testname and information about the test.
 *
 * @param the name of the test
 * @param information about the test
 */
void printTestInfo(char *testName, char *info)
{
    fprintf(stdout, "%s - %s\n", testName, info);
}

/**
 * Prints the testname and the results of the given test.
 *
 * @param the name of the test
 * @param the result of the test
 */
void printTestResult(char *testName, Boolean passed)
{
    if (passed == TRUE)
	fprintf(stdout, "%s - %s\n\n", "[PASSED]", testName);
    else
	fprintf(stdout, "%s - %s\n\n", "[FAILED]", testName);
}

/**
 * Creates the a node for the test
 *
 * @param the job information for a node
 */
NodePtr createTestNode(int jobid)
{
    ObjectPtr job = createObject(jobid, "cmd args");
    NodePtr node = createNode(job);
    freeObject(job);
    return node;
}

/**
 * Walks the through the list.  Every node is checked.
 *
 * @param a pointer to the list to be tested.
 */
Boolean walkList(ListPtr list)
{
    if (list->size == 0 && list->head != NULL) {
	myassert(list->head == NULL)
    }

    if (list->size == 0)
	return TRUE;

    NodePtr head = list->head;
    NodePtr tail = list->tail;
    NodePtr next = head->next;
    NodePtr prev = head->prev;

    myassert(head != NULL)
	myassert(tail != NULL)
	myassert(head->prev == NULL)
	myassert(tail->next == NULL)

	if (list->size == 1) {
	myassert(next == NULL)
	    myassert(prev == NULL)
	    return TRUE;
    }
    int count = 2;
    while (next != tail) {
	next = next->next;
	count++;
    }
    myassert(count == list->size)

	next = tail->prev;

    count = 2;
    while (next != head) {
	next = next->prev;
	count++;
    }
    myassert(count == list->size)

	return TRUE;
}

/**
 * Checks what happens when a node is added to the front of an empty list
 */
Boolean addAtFrontWithNoNodes()
{
    NodePtr node = createTestNode(1);

    addAtFront(testlist, node);

    myassert(testlist->size == 1)
	myassert(testlist->head == node)
	myassert(testlist->head->next == NULL)
	myassert(testlist->head->prev == NULL)

	if (!walkList(testlist)) {
	freeNode(node, freeObject);
	return FALSE;
    }


    return TRUE;
}

/**
 * Checks what happens when a node is added to the front of a list with one node
 */
Boolean addAtFrontWithOneNode()
{
    NodePtr node1 = createTestNode(1);
    NodePtr node2 = createTestNode(2);

    addAtFront(testlist, node1);
    walkList(testlist);
    addAtFront(testlist, node2);
    walkList(testlist);

    NodePtr node = testlist->head;
    myassert(testlist->size == 2)
	myassert(node == node2)
	myassert(node->next == node1)
	myassert(node->prev == NULL)
	node = node->next;
    myassert(node == node1)
	myassert(node->next == NULL)
	myassert(node->prev == node2)


	return TRUE;
}

/**
 * Checks what happens when a node is added to the rear of a list with no nodes
 */
Boolean addAtRearWithNoNodes()
{
    NodePtr node = createTestNode(1);

    addAtRear(testlist, node);

    myassert(testlist->size == 1)
	myassert(testlist->head == node)
	myassert(testlist->head->next == NULL)
	myassert(testlist->head->prev == NULL)

	walkList(testlist);


    return TRUE;
}

/**
 * Checks what happens when a node is added to the rear of a list with one node
 */
Boolean addAtRearWithOneNode()
{
    NodePtr node1 = createTestNode(1);
    NodePtr node2 = createTestNode(2);

    addAtRear(testlist, node1);
    walkList(testlist);
    addAtRear(testlist, node2);
    walkList(testlist);

    NodePtr node = testlist->head;

    myassert(testlist->size == 2)
	myassert(node == node1)
	myassert(node->next == node2)
	myassert(node->prev == NULL)

	node = node->next;

    myassert(node == node2)
	myassert(node->prev == node1)
	myassert(node->next == NULL)


	return TRUE;
}

/**
 * Adds ten nodes to a list using addAtFront and addAtRear, and checks the results
 */
Boolean addAtRearAndFront()
{
    NodePtr node1 = createTestNode(1);
    NodePtr node2 = createTestNode(2);
    NodePtr node3 = createTestNode(3);
    NodePtr node4 = createTestNode(4);
    NodePtr node5 = createTestNode(5);
    NodePtr node6 = createTestNode(6);
    NodePtr node7 = createTestNode(7);
    NodePtr node8 = createTestNode(8);
    NodePtr node9 = createTestNode(9);
    NodePtr node10 = createTestNode(10);



    addAtRear(testlist, node6);
    walkList(testlist);
    addAtFront(testlist, node5);
    walkList(testlist);
    addAtRear(testlist, node7);
    walkList(testlist);
    addAtFront(testlist, node4);
    walkList(testlist);
    addAtRear(testlist, node8);
    walkList(testlist);
    addAtFront(testlist, node3);
    walkList(testlist);
    addAtRear(testlist, node9);
    walkList(testlist);
    addAtFront(testlist, node2);
    walkList(testlist);
    addAtRear(testlist, node10);
    walkList(testlist);
    addAtFront(testlist, node1);
    walkList(testlist);

    NodePtr next = testlist->head;
    NodePtr prev = testlist->tail;

    myassert(testlist->size == 10)
	myassert(next == node1)
	myassert(prev == node10)
	myassert(next->prev == NULL)
	myassert(prev->next == NULL)
	next = next->next;
    prev = prev->prev;
    myassert(next == node2)
	myassert(prev == node9)
	next = next->next;
    prev = prev->prev;
    myassert(next == node3)
	myassert(prev == node8)
	next = next->next;
    prev = prev->prev;
    myassert(next == node4)
	myassert(prev == node7)
	next = next->next;
    prev = prev->prev;
    myassert(next == node5)
	myassert(prev == node6)
	next = next->next;
    prev = prev->prev;
    myassert(next == node6)
	myassert(prev == node5)
	next = next->next;
    prev = prev->prev;
    myassert(next == node7)
	myassert(prev == node4)
	next = next->next;
    prev = prev->prev;
    myassert(next == node8)
	myassert(prev == node3)
	next = next->next;
    prev = prev->prev;
    myassert(next == node9)
	myassert(prev == node2)
	next = next->next;
    prev = prev->prev;
    myassert(next == node10)
	myassert(prev == node1)
	next = next->next;
    prev = prev->prev;
    myassert(next == NULL);
    myassert(prev == NULL);

    return TRUE;
}

/**
 * Checks what happens when a node is removed from the front of a list with one node
 */
Boolean removeFromListWithOneNode1()
{
    NodePtr node = createTestNode(1);

    addAtFront(testlist, node);
    NodePtr n = removeFront(testlist);

    myassert(testlist->size == 0)
	myassert(testlist->head == NULL)
	myassert(testlist->tail == NULL)
	myassert(n->next == NULL)
	myassert(n->prev == NULL)

	freeNode(node, freeObject);

    return TRUE;
}

/**
 * Checks what happens when a node is removed from the rear of a list with one node
 */
Boolean removeFromListWithOneNode2()
{
    NodePtr node = createTestNode(1);

    addAtFront(testlist, node);
    NodePtr n = removeRear(testlist);

    myassert(testlist->size == 0)
	myassert(testlist->head == NULL)
	myassert(testlist->tail == NULL)
	myassert(n->next == NULL)
	myassert(n->prev == NULL)

	freeNode(node, freeObject);

    return TRUE;
}

/**
 * Checks what happens when a node is removed from the list given a node
 */
Boolean removeFromListWithOneNode3()
{
    NodePtr node = createTestNode(1);

    addAtFront(testlist, node);

    myassert(testlist != NULL)
	myassert(node != NULL)
	myassert(testlist->size == 1)
	myassert(testlist->head != NULL)
	myassert(testlist->head == node)
	myassert(testlist->head->next == NULL)
	myassert(testlist->head->prev == NULL)

    NodePtr n = removeNode(testlist, node);

    myassert(testlist->size == 0)
	myassert(testlist->head == NULL)
	myassert(testlist->tail == NULL)
	myassert(n->next == NULL)
	myassert(n->prev == NULL)

	freeNode(node, freeObject);

    return TRUE;
}

/**
 * Checks what happens when a node is removed from the front of a list with no nodes
 */
Boolean removeFromListWithNoNodes1()
{
    NodePtr n = removeFront(testlist);
    myassert(n == NULL)
	myassert(testlist->head == NULL)
	myassert(testlist->tail == NULL)

	return TRUE;
}

/**
 * Checks what happens when a node is removed from the rear of a list with no nodes
 */
Boolean removeFromListWithNoNodes2()
{
    NodePtr n = removeRear(testlist);
    myassert(n == NULL)
	myassert(testlist->head == NULL)
	myassert(testlist->tail == NULL)

	return TRUE;
}

/**
 * Checks what happens when a node is removed from a list given a node.
 */
Boolean removeFromListWithNoNodes3()
{
    NodePtr node = createTestNode(1);

    NodePtr n = removeNode(testlist, node->obj);
    myassert(n == NULL)
	myassert(testlist->head == NULL)
	myassert(testlist->tail == NULL)

	freeNode(node, freeObject);
    return TRUE;
}

/**
 * 10 nodes are added and then removed with all three of the remove methods.
 */
Boolean removeFromList()
{
    NodePtr node1 = createTestNode(1);
    NodePtr node2 = createTestNode(2);
    NodePtr node3 = createTestNode(3);
    NodePtr node4 = createTestNode(4);
    NodePtr node5 = createTestNode(5);
    NodePtr node6 = createTestNode(6);
    NodePtr node7 = createTestNode(7);
    NodePtr node8 = createTestNode(8);
    NodePtr node9 = createTestNode(9);
    NodePtr node10 = createTestNode(10);

    addAtRear(testlist, node6);
    addAtFront(testlist, node5);
    addAtRear(testlist, node7);
    addAtFront(testlist, node4);
    addAtRear(testlist, node8);
    addAtFront(testlist, node3);
    addAtRear(testlist, node9);
    addAtFront(testlist, node2);
    addAtRear(testlist, node10);
    addAtFront(testlist, node1);

    NodePtr n1 = removeNode(testlist, node1);
    myassert(testlist->size == 9)
	myassert(testlist->head == node2)
	myassert(testlist->tail == node10)
	myassert(testlist->head->next == node3)
	myassert(testlist->head->prev == NULL)
	myassert(testlist->tail->next == NULL)
	myassert(testlist->tail->prev == node9)
	myassert(n1->next == NULL)
	myassert(n1->prev == NULL)
	walkList(testlist);

    NodePtr n2 = removeRear(testlist);
    myassert(testlist->size == 8)
	myassert(testlist->head == node2)
	myassert(testlist->tail == node9)
	myassert(testlist->head->next == node3)
	myassert(testlist->head->prev == NULL)
	myassert(testlist->tail->next == NULL)
	myassert(testlist->tail->prev == node8)
	myassert(n2->next == NULL)
	myassert(n2->prev == NULL)
	walkList(testlist);

    NodePtr n3 = removeFront(testlist);
    myassert(testlist->size == 7)
	myassert(testlist->head == node3)
	myassert(testlist->tail == node9)
	myassert(testlist->head->next == node4)
	myassert(testlist->head->prev == NULL)
	myassert(testlist->tail->next == NULL)
	myassert(testlist->tail->prev == node8)
	myassert(n3->next == NULL)
	myassert(n3->prev == NULL)
	walkList(testlist);

    NodePtr n4 = removeNode(testlist, node9);
    myassert(testlist->size == 6)
	myassert(testlist->head == node3)
	myassert(testlist->tail == node8)
	myassert(testlist->head->next == node4)
	myassert(testlist->head->prev == NULL)
	myassert(testlist->tail->next == NULL)
	myassert(testlist->tail->prev == node7)
	myassert(n4->next == NULL)
	myassert(n4->prev == NULL)
	walkList(testlist);

    NodePtr n5 = removeFront(testlist);
    myassert(testlist->size == 5)
	myassert(testlist->head == node4)
	myassert(testlist->tail == node8)
	myassert(testlist->head->next == node5)
	myassert(testlist->head->prev == NULL)
	myassert(testlist->tail->next == NULL)
	myassert(testlist->tail->prev == node7)
	myassert(n5->next == NULL)
	myassert(n5->prev == NULL)
	walkList(testlist);

    NodePtr n6 = removeRear(testlist);
    myassert(testlist->size == 4)
	myassert(testlist->head == node4)
	myassert(testlist->tail == node7)
	myassert(testlist->head->next == node5)
	myassert(testlist->head->prev == NULL)
	myassert(testlist->tail->next == NULL)
	myassert(testlist->tail->prev == node6)
	myassert(n6->next == NULL)
	myassert(n6->prev == NULL)
	walkList(testlist);

    NodePtr n7 = removeNode(testlist, node5);
    myassert(testlist->size == 3)
	myassert(testlist->head == node4)
	myassert(testlist->tail == node7)
	myassert(testlist->head->next == node6)
	myassert(testlist->head->prev == NULL)
	myassert(testlist->tail->next == NULL)
	myassert(testlist->tail->prev == node6)
	myassert(n7->next == NULL)
	myassert(n7->prev == NULL)
	walkList(testlist);

    NodePtr n8 = removeNode(testlist, node6);
    myassert(testlist->size == 2)
	myassert(testlist->head == node4)
	myassert(testlist->tail == node7)
	myassert(testlist->head->next == node7)
	myassert(testlist->head->prev == NULL)
	myassert(testlist->tail->next == NULL)
	myassert(testlist->tail->prev == node4)
	myassert(n8->next == NULL)
	myassert(n8->prev == NULL)
	walkList(testlist);

    NodePtr n9 = removeFront(testlist);
    myassert(testlist->size == 1)
	myassert(testlist->head == node7)
	myassert(testlist->tail == node7)
	myassert(testlist->head->next == NULL)
	myassert(testlist->head->prev == NULL)
	myassert(testlist->tail->next == NULL)
	myassert(testlist->tail->prev == NULL)
	myassert(n9->next == NULL)
	myassert(n9->prev == NULL)
	walkList(testlist);

    NodePtr n10 = removeRear(testlist);
    myassert(testlist->size == 0)
	myassert(testlist->head == NULL)
	myassert(testlist->tail == NULL)
	myassert(n10->next == NULL)
	myassert(n10->prev == NULL)

	freeNode(node1, freeObject);
    freeNode(node2, freeObject);
    freeNode(node3, freeObject);
    freeNode(node4, freeObject);
    freeNode(node5, freeObject);
    freeNode(node6, freeObject);
    freeNode(node7, freeObject);
    freeNode(node8, freeObject);
    freeNode(node9, freeObject);
    freeNode(node10, freeObject);

    return TRUE;
}

/**
 * Checks what happens when a null node is added to the front of a list
 */
Boolean nullNodeTest1()
{
    NodePtr node = NULL;
    addAtFront(testlist, node);
    myassert(testlist->size == 0)
	myassert(testlist->head == NULL)
	myassert(testlist->tail == NULL)

	return TRUE;
}

/**
 * Checks what happens when a null node is added to the rear of a list
 */
Boolean nullNodeTest2()
{
    NodePtr node = NULL;
    addAtRear(testlist, node);
    myassert(testlist->size == 0)
	myassert(testlist->head == NULL)
	myassert(testlist->tail == NULL)

	return TRUE;
}

/**
 * Checks what happens when a null node is removed from the list given a node
 */
Boolean nullNodeTest3()
{
    NodePtr node = NULL;
    NodePtr n = removeNode(testlist, node);
    myassert(testlist->size == 0)
	myassert(testlist->head == NULL)
	myassert(testlist->tail == NULL)
	myassert(n == NULL)

	return TRUE;
}

/**
 * Checks what happens when a null node is removed from the rear of the list
 */
Boolean nullNodeTest4()
{
    NodePtr n = removeRear(testlist);
    myassert(testlist->size == 0)
	myassert(testlist->head == NULL)
	myassert(testlist->tail == NULL)
	myassert(n == NULL)

	return TRUE;
}

/**
 * Checks what happens when a null node is removed from the front of the list
 */
Boolean nullNodeTest5()
{
    NodePtr n = removeFront(testlist);
    myassert(testlist->size == 0)
	myassert(testlist->head == NULL)
	myassert(testlist->tail == NULL)
	myassert(n == NULL)

	return TRUE;
}

/**
 * Checks what happens when the list is reversed with one node
 */
Boolean reverseTest1()
{
    NodePtr node1 = createTestNode(1);
    addAtFront(testlist, node1);

    reverseList(testlist);
    myassert(testlist->head == node1)
	myassert(testlist->tail == node1)
	myassert(testlist->size == 1)
	myassert(testlist->head->next == NULL)
	myassert(testlist->head->prev == NULL)
	myassert(testlist->tail->next == NULL)
	myassert(testlist->tail->prev == NULL)

	freeNode(node1, freeObject);

    return TRUE;
}

/**
 * Checks what happens when the list is reversed with two nodes
 */
Boolean reverseTest2()
{
    NodePtr node1 = createTestNode(1);
    NodePtr node2 = createTestNode(2);
    addAtFront(testlist, node2);
    addAtFront(testlist, node1);

    reverseList(testlist);
    myassert(testlist->head == node2);
    myassert(testlist->tail == node1);
    myassert(testlist->size == 2)
	myassert(testlist->head->next == node1)
	myassert(testlist->head->prev == NULL)
	myassert(testlist->tail->next == NULL)
	myassert(testlist->tail->prev == node2)

	freeNode(node1, freeObject);
    freeNode(node2, freeObject);

    return TRUE;
}

/**
 * Checks what happens when the list is reversed with three nodes
 */
Boolean reverseTest3()
{
    NodePtr node1 = createTestNode(1);
    NodePtr node2 = createTestNode(2);
    NodePtr node3 = createTestNode(3);
    addAtFront(testlist, node3);
    addAtFront(testlist, node2);
    addAtFront(testlist, node1);

    reverseList(testlist);
    myassert(testlist->head == node3);
    myassert(testlist->tail == node1);
    myassert(testlist->size == 3)
	myassert(testlist->head->next == node2)
	myassert(testlist->head->prev == NULL)
	myassert(testlist->tail->next == NULL)
	myassert(testlist->tail->prev == node2)

	freeNode(node1, freeObject);
    freeNode(node2, freeObject);
    freeNode(node3, freeObject);

    return TRUE;
}

/**
 * Checks what happens when the list is reversed with four nodes
 */
Boolean reverseTest4()
{
    NodePtr node1 = createTestNode(1);
    NodePtr node2 = createTestNode(2);
    NodePtr node3 = createTestNode(3);
    NodePtr node4 = createTestNode(4);
    addAtFront(testlist, node4);
    addAtFront(testlist, node3);
    addAtFront(testlist, node2);
    addAtFront(testlist, node1);

    reverseList(testlist);
    myassert(testlist->head == node4);
    myassert(testlist->tail == node1);
    myassert(testlist->size == 4)
	myassert(testlist->head->next == node3)
	myassert(testlist->head->prev == NULL)
	myassert(testlist->tail->next == NULL)
	myassert(testlist->tail->prev == node2)

	freeNode(node1, freeObject);
    freeNode(node2, freeObject);
    freeNode(node3, freeObject);
    freeNode(node4, freeObject);

    return TRUE;
}

/**
 * Creates the list and keeps count of how many tests there are
 *
 * @param the name of the test
 */
void beforeTest(char *testName)
{
    printTestInfo(testName, "Running...");
    testlist = createList(equals, toString, freeObject);
    testCount++;
}

/**
 * Calls the prints function and then frees the list
 *
 * @param the name of the test
 * @param the result of the test
 */
void afterTest(char *testName, Boolean result)
{
    printTestResult(testName, result);
    freeList(testlist);
    passCount += result;
}

/**
 * Calls all of the test functions
 */
void runUnitTests()
{
    Boolean result;
    char *testName;

    testName = "addAtFrontWithNoNodes";
    beforeTest(testName);
    result = addAtFrontWithNoNodes();
    afterTest(testName, result);

    testName = "addAtFrontWithOneNode";
    beforeTest(testName);
    result = addAtFrontWithOneNode();
    afterTest(testName, result);

    testName = "addAtRearWithNoNodes";
    beforeTest(testName);
    result = addAtRearWithNoNodes();
    afterTest(testName, result);

    testName = "addAtRearWithOneNode";
    beforeTest(testName);
    result = addAtRearWithOneNode();
    afterTest(testName, result);

    testName = "addAtRearAndFront";
    beforeTest(testName);
    result = addAtRearAndFront();
    afterTest(testName, result);

    testName = "removeFromListWithOneNode1";
    beforeTest(testName);
    result = removeFromListWithOneNode1();
    afterTest(testName, result);

    testName = "removeFromListWithOneNode2";
    beforeTest(testName);
    result = removeFromListWithOneNode2();
    afterTest(testName, result);

    testName = "removeFromListWithOneNode3";
    beforeTest(testName);
    result = removeFromListWithOneNode3();
    afterTest(testName, result);

    testName = "removeFromListWithNoNodes1";
    beforeTest(testName);
    result = removeFromListWithNoNodes1();
    afterTest(testName, result);

    testName = "removeFromListWithNoNodes2";
    beforeTest(testName);
    result = removeFromListWithNoNodes2();
    afterTest(testName, result);

    testName = "removeFromListWithNoNodes3";
    beforeTest(testName);
    result = removeFromListWithNoNodes3();
    afterTest(testName, result);

    testName = "removeFromList";
    beforeTest(testName);
    result = removeFromList();
    afterTest(testName, result);

    testName = "nullNodeTest1";
    beforeTest(testName);
    result = nullNodeTest1();
    afterTest(testName, result);

    testName = "nullNodeTest2";
    beforeTest(testName);
    result = nullNodeTest2();
    afterTest(testName, result);

    testName = "nullNodeTest3";
    beforeTest(testName);
    result = nullNodeTest3();
    afterTest(testName, result);

    testName = "nullNodeTest4";
    beforeTest(testName);
    result = nullNodeTest4();
    afterTest(testName, result);

    testName = "nullNodeTest5";
    beforeTest(testName);
    result = nullNodeTest5();
    afterTest(testName, result);

    testName = "reverseTest1";
    beforeTest(testName);
    result = reverseTest1();
    afterTest(testName, result);

    testName = "reverseTest2";
    beforeTest(testName);
    result = reverseTest2();
    afterTest(testName, result);

    testName = "reverseTest3";
    beforeTest(testName);
    result = reverseTest3();
    afterTest(testName, result);

    testName = "reverseTest4";
    beforeTest(testName);
    result = reverseTest4();
    afterTest(testName, result);

    //etc...

    fprintf(stdout, "Test Cases: %d\n", testCount);
    fprintf(stdout, "Passed: %d\n", passCount);
    fprintf(stdout, "Failed: %d\n", testCount - passCount);
}

/**
 * Calls the function that runs all of tests.
 *
 * @param size of the argument array
 * @param the argument array
 */
int main(int argc, char *argv[])
{
    runUnitTests();
    exit(0);
}
