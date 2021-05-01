
#define _CRT_SECURE_NO_WARNINGS
typedef struct sListElem {
	void* data;
	struct sListElem* next;
} *ListElem, SListElem;

typedef struct sListLists {
	struct sListElem* list;
	struct sListLists* next;
}*LISTofLISTS;

//functions to add items to list and list of lists and print them
ListElem addItem(ListElem list, void* value);
LISTofLISTS addItem2(LISTofLISTS list1, ListElem list2);
void printList(ListElem list);
void printList2(LISTofLISTS list);

LISTofLISTS readFile();


// Insert a new element with *data in the head of the list 
// *data must point to storage in the heap
ListElem addItemHead(ListElem head, void* data);

// Applies show function to all elements on the list, iteratively
void showListIterative(ListElem head, void (*show)(void* data));

// Applies show function to all elements on the list, recursively
void showListRecursive(ListElem head, void (*show)(void* data));

// Insert a new element with *data in last position of the list, iteratively
// *data must point to storage in the heap
ListElem addItemLastIterative(ListElem head, void* data);

// Insert a new element with *data in last position of the list, recursively
// *data must point to storage in the heap
ListElem addItemLastRecursive(ListElem head, void* data);

// Insert a new element with *data in the list according to the order defined by function compare, iteratively
// *data must point to storage in the heap
ListElem addItemOrderedIterative(ListElem head, void* data, int (*compare)(void* data1, void* data2));

// Insert a new element with *data in the list according to the order defined by functoin compare, recursively
// *data must point to storage in the heap
ListElem addItemOrderedRecursive(ListElem head, void* data, int (*compare)(void* data1, void* data2));

// Removes the first item on the list that compares positively with *data through function compare, iteratively 
ListElem removeItemIterative(ListElem head, void* data, int (*compare)(void* data1, void* data2));

// Removes the first item on the list that compares positively with *data through function compare, recursively
ListElem removeItemRecursive(ListElem head, void* data, int (*compare)(void* data1, void* data2));
