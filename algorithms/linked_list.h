#ifndef __LINKED_LIST__
#define __LINKED_LIST__

#define OK 0
#define FAILED -1

#define TRUE 1
#define FALSE 0

typedef void* T;
typedef int bool;

typedef struct Element{
	T data;
	struct Element *next;
	struct Element *prev;
}Element, *ElementRef;
	
typedef struct LinkedList {
	int size;
	ElementRef head;
	ElementRef tail;
	void (*destroy)(T);
	bool (*compare)(T, T);
}LinkedList, *LinkedListRef;

#define list_size(list) ((list)->size)

LinkedListRef list_init(void (*destroy)(T), bool (*compare)(T, T));
bool list_insert_first(LinkedListRef list, T data);
bool list_insert_last(LinkedListRef list, T data);
int list_insert_at(LinkedListRef list, T data, int index);

T list_get(LinkedListRef list, int index);
T list_get_first(LinkedListRef list);
T list_get_last(LinkedListRef list);

T list_remove_first(LinkedListRef list);
T list_remove_last(LinkedListRef list);
T list_remove_at(LinkedListRef list, int index);

void list_destroy(LinkedListRef list);

#endif