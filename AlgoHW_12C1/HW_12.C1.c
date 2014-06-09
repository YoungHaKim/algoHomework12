/*
141020 김영하

HW#12.C1
 수업 시간에 완료하지 못한 실습 주제들
*/

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node *next;
} node_t;

typedef struct list
{
	struct node *head;
} list_t;

void doSearch(list_t *list, int value);
void delete(list_t *list, node_t *prevNode, node_t *targetNode);
void insertNode(list_t *list, node_t *nodeA, node_t *nodeB);
void insertNodeAtFront(list_t *list, node_t *node);
void insertNodeAfterNode(node_t *nodeA, node_t* nodeB);
void printAllNodes(list_t *list);
void printList(list_t *list);
node_t *searchForNode(list_t *list, int data);
node_t *searchForNodePrev(list_t *list, int data);
node_t *createNodeWithValue(int value);

int main()
{	
	list_t list;
	list.head = NULL;
	
	node_t *node1 = createNodeWithValue(10);
	node_t *node2 = createNodeWithValue(20);
	node_t *node3 = createNodeWithValue(30);
	node_t *node4 = createNodeWithValue(40);
	node_t *node5 = createNodeWithValue(50);
	node_t *node6 = createNodeWithValue(100);
	
	insertNodeAtFront(&list, node1);
	insertNodeAfterNode(node1, node2);
	insertNodeAfterNode(node2, node3);
	insertNodeAfterNode(node3, node4);
	insertNodeAfterNode(node4, node5);
	insertNodeAfterNode(node5, node6);

	printf("\n실습 1-2\n");
	printList(&list);

	printf("\n실습 3-4\n");
	printAllNodes(&list);

	printf("\n실습 5\n");
	doSearch(&list, 30);
	doSearch(&list, 70);

	printf("\n실습 7\n");
	node_t *targetNode = searchForNode(&list, 40);
	node_t *newNode1 = createNodeWithValue(45);
	insertNode(&list, targetNode, newNode1);
	printAllNodes(&list);

	node_t *newNode2 = createNodeWithValue(5);
	insertNode(&list, NULL, newNode2);
	printAllNodes(&list);

	printf("\n실습 9\n");
	node_t *deleteNode = searchForNode(&list, 40);
	node_t *deleteNodePrev = searchForNodePrev(&list, 40);
	delete(&list, deleteNodePrev, deleteNode);
	printAllNodes(&list);

	while (list.head)
	{
		delete(&list, NULL, list.head);
	}
	printAllNodes(&list);

	getchar();

	return 0;
}

// 실습 주제 5
void doSearch(list_t *list, int value)
{
	node_t *searchNode = searchForNode(list, value);
	if (searchNode)
	{
		printf("found value %d\n", searchNode->data);
	}
	else printf("Value %d not found\n", value);
}

node_t *createNodeWithValue(int value)
{
	node_t *node = (node_t*)malloc(sizeof(node_t));

	node->data = value;
	node->next = NULL;

	return node;
}

node_t *searchForNode(list_t *list, int data)
{
	node_t *currentNode;

	if (list == NULL) return (node_t*)NULL;

	currentNode = list->head;

	while (currentNode != NULL)
	{
		if (currentNode->data == data)
			return currentNode;

		currentNode = currentNode->next;
	}

	return (node_t*)NULL;
}

node_t *searchForNodePrev(list_t *list, int data)
{
	node_t *currentNode;

	if (list == NULL) return (node_t*)NULL;

	currentNode = list->head;

	while (currentNode != NULL)
	{
		if (currentNode->next)
		{
			if (currentNode->next->data == data)
				return currentNode;
		}

		currentNode = currentNode->next;
	}

	return (node_t*)NULL;
}

// 실습 주제 2
void printList(list_t *list)
{
	node_t *currentNode;

	if (list == NULL) return;

	currentNode = list->head;

	while (currentNode != NULL)
	{
		if (currentNode->next != NULL)
			printf("%d, %X, %d \n", currentNode->data, currentNode->next, currentNode->next->data);
		else
			printf("%d, NULL, none \n", currentNode->data);

		currentNode = currentNode->next;
	}
}


// 실습 주제 3
void printAllNodes(list_t *list)
{
	printf("list: [ ");

	node_t *currentNode;

	if (list == NULL) return;

	currentNode = list->head;

	while (currentNode != NULL)
	{
		printf("%d -> ", currentNode->data);		

		currentNode = currentNode->next;
	}

	printf(" ]\n");
}

// 실습 주제 8
void delete(list_t *list, node_t *prevNode, node_t *targetNode)
{
	if (list == NULL || targetNode == NULL) return;

	if (prevNode != NULL) {
		prevNode->next = targetNode->next;	
	} else {
		list->head = list->head->next;		//prevN이 NULL인 경우는 targetN이 list의 head인 경우임
	}

	free(targetNode);
}

/*
실습 주제 6

임의의 node A다음에 node B 추가
 만약 주어진 node A가 null이면 리스트의 맨앞에 node B 추가
*/
void insertNode(list_t *list, node_t *nodeA, node_t *nodeB)
{
	if (list == NULL || nodeB == NULL) return;

	if (nodeA != NULL)
	{
		nodeB->next = nodeA->next;
		nodeA->next = nodeB;
	}
	else
	{
		nodeB->next = list->head;
		list->head = nodeB;
	}
}

///
/// Insert node B after node A
void insertNodeAfterNode(node_t *nodeA, node_t* nodeB)
{
	if (nodeA == NULL || nodeB == NULL) return;

	nodeB->next = nodeA->next;
	nodeA->next = nodeB;
}


// 실습 주제 4
void insertNodeAtFront(list_t *list, node_t *node)
{
	if (list == NULL || node == NULL) return;

	if (list->head != NULL)
	{
		node->next = list->head;
		list->head = node;
	}
	else
	{
		list->head = node;
	}
}