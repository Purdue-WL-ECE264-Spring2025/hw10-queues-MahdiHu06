#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) {
	struct list_node *newNode = malloc(sizeof(struct list_node));
	newNode -> value = value;
	newNode -> next = NULL;
	return newNode;
}

void insert_at_head(struct linked_list *list, size_t value) {
	struct list_node* newNode = new_node(value);
	if(list->head == NULL)
	{
		newNode->next = list->head;
	}
	list->head = newNode;	
}

void insert_at_tail(struct linked_list *list, size_t value) {
	struct list_node* newNode = new_node(value);
	struct list_node* head = list->head;
	if(head)
	{
		while(head->next)
		{
			head = head->next;
		}
		head->next = newNode;
	} else {
		list->head = newNode;
	}
}

size_t remove_from_head(struct linked_list *list) { 
	struct list_node* removed = list->head;
	if(removed)
	{
		list->head = list->head->next;
		free(removed);
	}
	return 0; 
}

size_t remove_from_tail(struct linked_list *list) {
	struct list_node* head = list->head;

	if(head)
	{
		if(head->next){
			while(head->next->next)
			{
				head = head->next;
			}
			free(head->next);
			head->next = NULL;
		} else {
			free(head);
			list->head = NULL;	
		}
	}
	return 0;
}

void free_list(struct linked_list list) {
	while(list.head)
	{
		remove_from_head(&list);
	}
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
	fprintf(fp, "[ ");
	for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
		fprintf(fp, "%zu ", cur->value);
	}
	fprintf(fp, "]\n");
}
