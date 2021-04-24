#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ll.h"

ListElem addItem(ListElem list, void* value)
{
	if (list == NULL)
	{
		ListElem newList = malloc(sizeof(ListElem));
		newList->data = value;
		newList->next = NULL;
		list = newList;
		return list;
	}
	else
	{
		ListElem aux = list;
		while (list->next != NULL)
		{
			list = list->next;
		}
		ListElem newItem = malloc(sizeof(ListElem));
		newItem->data = value;
		newItem->next = NULL;
		list->next = newItem;
		list = aux;
		return list;
	}
}

LISTofLISTS addItem2(LISTofLISTS list1, ListElem list2)
{
	if (list1 == NULL)
	{
		LISTofLISTS newList = malloc(sizeof(LISTofLISTS));
		newList->list = list2;
		newList->next = NULL;
		list1 = newList;
		return list1;
	}
	else
	{
		LISTofLISTS aux = list1;
		while (list1->next != NULL)
		{
			list1 = list1->next;
		}
		LISTofLISTS newItem = malloc(sizeof(LISTofLISTS));
		newItem->list = list2;
		newItem->next = NULL;
		list1->next = newItem;
		list1 = aux;
		return list1;
	}
}

void printList(ListElem list)
{
	ListElem aux = list;
	while (aux != NULL)
	{
		printf("%d -> ", aux->data);
		aux = aux->next;
	}
}

void printList2(ListElem list)
{
	LISTofLISTS aux = list;
	while (aux != NULL)
	{
		printList(aux->list);
		printf("\n");
		aux = aux->next;
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

