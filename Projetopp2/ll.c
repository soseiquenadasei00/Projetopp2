#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ll.h"

/*Read text file*/
LISTofLISTS readFile()
{
	char address[200] = { 0 };
	char line[100] = { 0 };

	printf("Data address: ");

	scanf("%s", &address);

	FILE* file = NULL;
	file = fopen(address, "r");

	if (file != NULL)
	{
		// printf("checkpoint 1\n");
		LISTofLISTS returnList = NULL;
		//file = fopen(address, "r");
		while (fgets(line, 200, file))
		{
			ListElem dataList1 = NULL;
			ListElem tempList = NULL;

			for (int i = 0; i < strlen(line); i++)
			{
				//if blank sapce or new line command found, add item to data list and set item to nothing
				if (line[i] == 32 || line[i] == 10)//espaço e nova linha
				{
					// printf("checkpoint 2\n");
					dataList1 = addItem(dataList1, (ListElem*)tempList);
					// printList(dataList1);
					// printf("\n");
					tempList = NULL;
				}
				else//add char to item found
				{
					//palavra a ser formada
					// printf("checkpoint 3\n");
					tempList = addItem(tempList, line[i]);
					// printElement(tempList);
					// printf("\n");
				}
			}
			returnList = addItem2(returnList, dataList1);
		}
		fclose(file);
		// printf("Leitura Realizada\n");
		return returnList;
	}
	else
	{
		fclose(file);
		return NULL;
	}
}

/*add items to a linked list of type ListElem*/
ListElem addItem(ListElem list, void* value)
{
	int index = 0;
	if (list == NULL)
	{
		ListElem newList = (struct sListElem*)malloc(sizeof(ListElem));
		newList->data = (void*)value;
		newList->next = NULL;
		newList->index = index;
		list = newList;
		return list;
	}
	else
	{
		ListElem aux = list;
		while (list->next != NULL)
		{
			list = list->next;
			index = list->index;
		}
		ListElem newItem = (struct sListElem*)malloc(sizeof(ListElem));
		newItem->data = (void*)value;
		newItem->next = NULL;
		newItem->index = index + 1;
		list->next = newItem;
		list = aux;
		return list;
	}
}

ListElem addHead(ListElem list, void* value)
{
	int index = 0;
	if (list == NULL)
	{
		ListElem newList = (struct sListElem*)malloc(sizeof(ListElem));
		newList->data = (void*)value;
		newList->next = NULL;
		newList->index = index;
		list = newList;
		return list;
	}
	else
	{
		ListElem newItem = (struct sListElem*)malloc(sizeof(ListElem));
		newItem->data = (void*)value;
		newItem->next = list;
		newItem->index = index;	
		return newItem;
	}
}
/*add items to a linked list of type LISTofLISTS*/
LISTofLISTS addItem2(LISTofLISTS list1, ListElem list2)
{
	int index = 0;
	if (list1 == NULL)
	{
		LISTofLISTS newList = (struct sListLists*)malloc(sizeof(LISTofLISTS));
		newList->list = list2;
		newList->next = NULL;
		newList->index = index;
		list1 = newList;
		return list1;
	}
	else
	{
		//manter a origem da lista ligada
		LISTofLISTS aux = list1;
		while (list1->next != NULL)
		{
			list1 = list1->next;
			index = list1->index;
		}
		LISTofLISTS newItem = (struct sListLists*)malloc(sizeof(LISTofLISTS));
		newItem->list = list2;
		newItem->next = NULL;
		newItem->index = index + 1;
		list1->next = newItem;
		list1 = aux;
		return list1;
	}
}

/*prints linked list with data types linked list*/
void printList(ListElem list)
{
	ListElem aux = list;

	while (aux != NULL)
	{
		ListElem word = aux->data;
		while (word != NULL)
		{
			printf("%c", word->data);
			word = word->next;
		}
		printf(" ");
		aux = aux->next;
	}
	printf("\n");
}
/*prints element of linked list*/
void printElement(ListElem list)
{
	ListElem aux = list;

	while (aux != NULL)
	{
		printf("%c", aux->data);
		aux = aux->next;
	}
}

/*prints the lists inside a linked list*/
void printList2(LISTofLISTS list)
{
	LISTofLISTS aux = list;
	while (aux != NULL)
	{
		printList(aux->list);
		printf("\n");
		aux = aux->next;
	}
}

ListElem getDataOfListElem(ListElem list, int index)
{
	ListElem aux = list;
	while (aux != NULL)
	{
		if (aux->index == index)
		{
			break;
		}
		aux = aux->next;
	}

	if (aux != NULL && aux->index == index)
	{
		// printf("Found element\n\n");
		return aux->data;
	}
	else
	{
		// printf("Found nothing\n\n");
		return NULL;
	}

}
ListElem getDataOfLISTofLISTS(LISTofLISTS list, int index)
{
	if (list != NULL)
	{
		LISTofLISTS aux = list;
		while (aux != NULL && aux->index != index)
		{
			aux = aux->next;
		}

		if (aux != NULL)
		{
			return aux->list;
		}
	}
	return NULL;
}

int ListSize(ListElem list)
{
	if (list == NULL)
	{
		//printf("ListELem size: 0\n");
		return 0;
	}
	else
	{
		ListElem aux = list;
		int counter = 0;
		while (aux != NULL)
		{
			++counter;
			aux = aux->next;
		}
		//printf("ListELem size: %d\n", counter);
		return counter;
	}
}

int ListOFListsSize(LISTofLISTS list)
{
	if (list == NULL)
	{
		return 0;
	}
	else
	{
		LISTofLISTS aux = list;
		int counter = 0;
		while (aux != NULL)
		{
			++counter;
			aux = aux->next;
		}
		printf("ListOFLists size: %d\n", counter);
		return counter;
	}
}

ListElem addItemHead(ListElem head, void* data) {
	ListElem aux;

	if ((aux = (ListElem)malloc(sizeof(SListElem))) == NULL)
		return head;

	aux->data = data;
	aux->next = head;

	return aux;
}

ListElem addItemLastRecursive(ListElem head, void* data) {
	ListElem aux;

	if (head == NULL) {
		aux = (ListElem)malloc(sizeof(SListElem));
		aux->data = data;
		aux->next = NULL;
		return aux;
	}

	head->next = addItemLastRecursive(head->next, data);

	return head;
}

ListElem addItemLastIterative(ListElem head, void* data) {
	ListElem aux, prev;

	aux = (ListElem)malloc(sizeof(SListElem));
	aux->data = data;
	aux->next = NULL;

	if (head == NULL) {
		return aux;
	}

	for (prev = head; prev->next != NULL; prev = prev->next)
		;

	prev->next = aux;

	return head;
}

void showListIterative(ListElem head, void (*show)(void* data)) {

	while (head != NULL) {
		show(head->data);
		head = head->next;
	}

}

void showListRecursive(ListElem head, void (*show)(void* data)) {
	if (head != NULL) {
		show(head->data);
		showListRecursive(head->next, show);
	}
}

ListElem removeItemIterative(ListElem head, void* data, int (*compare)(void* data1, void* data2)) {
	ListElem aux, prev;

	// List is empty
	if (head == NULL)
		return NULL;

	// Element to remove is on the head of the list
	if (compare(head->data, data) == 1) {
		aux = head->next;
		free(head);
		return aux;
	}

	// Element to remove is in the tail of the list
	for (prev = head; prev->next != NULL; prev = prev->next)
	{
		if (compare(prev->next->data, data) == 1) {
			aux = prev->next;
			prev->next = prev->next->next;
			free(aux);
			break;
		}
	}

	return head;
}

ListElem removeItemRecursive(ListElem head, void* data, int (*compare)(void* data1, void* data2)) {
	ListElem aux;

	if (head == NULL)
		return NULL;

	if (compare(head->data, data) == 1) {
		aux = head->next;
		free(head);
		return aux;
	}
	else {
		head->next = removeItemRecursive(head->next, data, compare);
		return head;
	}
}

ListElem addItemOrderedIterative(ListElem head, void* data, int (*compare)(void* data1, void* data2)) {
	ListElem n, aux;

	n = (ListElem)malloc(sizeof(SListElem));
	n->data = data;
	n->next = NULL;

	if (head == NULL || compare(data, head->data) < 0) {
		n->next = head;
		return n;
	}

	for (aux = head; aux->next != NULL; aux = aux->next) {
		if (compare(data, aux->next->data) < 0) {
			n->next = aux->next;
			aux->next = n;
			return head;
		}
	}

	aux->next = n;
	return head;
}

ListElem addItemOrderedRecursive(ListElem head, void* data, int (*compare)(void* data1, void* data2)) {
	ListElem aux;

	if (head == NULL || compare(data, head->data) < 0) {
		aux = (ListElem)malloc(sizeof(SListElem));
		aux->data = data;
		aux->next = head;
		return aux;
	}

	head->next = addItemOrderedRecursive(head->next, data, compare);
	return head;
}

