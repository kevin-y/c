#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

LinkedListRef list_init(void (*destroy)(T), bool (*compare)(T, T)) {
	LinkedListRef list = (LinkedListRef)malloc(sizeof(LinkedList));
	if(list == NULL) {
		perror("ERROR: OutOfMemoryError\n");
		return NULL;
	}

	list->size = 0;
	list->head = NULL;
	list->tail = NULL;
	list->destroy = destroy;
	list->compare = compare;
	return list;
}

bool list_insert_first(LinkedListRef list, T data) {
	ElementRef element = (ElementRef)malloc(sizeof(Element));
	if(element == NULL) {
		perror("ERROR: OutOfMemoryError\n");
		return FALSE;
	}

	element->data = data;
	element->prev = NULL;

	if(list_size(list) == 0) {
		list->tail = element;
		element->next = NULL;
	} else {
		list->head->prev = element;
		element->next = list->head;
	}
	list->head = element;
	list->size++;
	return TRUE;
}

bool list_insert_last(LinkedListRef list, T data) {
	ElementRef element = (ElementRef)malloc(sizeof(Element));
	if(element == NULL) {
		perror("ERROR: OutOfMemoryError\n");
		return FALSE;
	}

	element->data = data;
	element->next = NULL;

	if(list_size(list) == 0) {
		list->head = element;
		element->prev = NULL;
	} else {
		list->tail->next = element;
		element->prev = list->tail;
	}
	list->tail = element;
	list->size++;
	return TRUE;
}

int list_insert_at(LinkedListRef list, T data, int index) {

	if(index == list_size(list)) {
		return list_insert_last(list, data);
	}

	ElementRef element = (ElementRef)malloc(sizeof(Element));
	if(element == NULL) {
		perror("ERROR: OutOfMemoryError\n");
		return FALSE;
	}

	ElementRef p = list->head;

	int i;
	for(i = 1; i < index; i++) {
		p = p->next;
	}

	element->data = data;
	element->prev = p;
	element->next = p->next;
	p->next->prev = element;
	p->next = element;
	list->size++;
	return TRUE;
}

T list_get(LinkedListRef list, int index) {
	if(list_size(list) <= index) {
		perror("ERROR: OutOfBoundError\n");
		return NULL;
	}

	ElementRef p = list->head;
	int i;
	for(i = 0; i < index; i++) {
		p = p->next;
	}

	return p->data;
}

T list_get_first(LinkedListRef list) {
	if(list_size(list) == 0) {
		printf("WARNING: No data.\n");
		return NULL;
	}
	return list->head->data;
}

T list_get_last(LinkedListRef list) {
	if(list_size(list) == 0) {
		printf("WARNING: No data.\n");
		return NULL;
	}
	return list->tail->data;
}


T list_remove_first(LinkedListRef list) {
	if(list_size(list) == 0) {
		printf("WARNING: No data.\n");
		return NULL;
	}

	ElementRef p = list->head;
	if(p->next != NULL)
		p->next->prev = NULL;
	list->head = p->next;
	list->size--;
	if(list_size(list) == 0) {
		list->tail = NULL;
	}
	T data = p->data;
	free(p);
	p = NULL;
	return data;
}

T list_remove_last(LinkedListRef list) {
	if(list_size(list) == 0) {
		printf("WARNING: No data.\n");
		return NULL;
	}

	ElementRef p = list->tail;
	list->tail = p->prev;
	list->tail->next = NULL;
	list->size--;
	if(list_size(list) == 0)
		list->head = NULL;
	T data = p->data;
	free(p);
	p = NULL;
	return data;
}

T list_remove_at(LinkedListRef list, int index) {
	if(index == 0) {
		return list_remove_first(list);
	}

	if(index == (list_size(list) - 1)) {
		return list_remove_last(list);
	}

	ElementRef p = list->head;
	int i;
	for(i = 0; i < index; i++) {
		p = p->next;
	}

	T data = p->data;
	p->prev->next = p->next;
	p->next->prev = p->prev;
	list->size--;
	free(p);
	p = NULL;
	return data;
}

void list_destroy(LinkedListRef list) {
	if(list == NULL) return;
	while(list_size(list) > 0) {
		if(list->destroy != NULL) {
			list->destroy(list_remove_first(list));
		} else {
			list_remove_first(list);
		}
	}
	free(list);
	list = NULL;
}
