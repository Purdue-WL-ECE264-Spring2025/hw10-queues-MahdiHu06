#include "linked_list.h"
#include <stdlib.h>

// create a new node
struct list_node *new_node(size_t value) { 
	struct list_node *newNode = malloc(sizeof(struct list_node));
	if(newNode == NULL){return NULL;}
	newNode->next = NULL;
	newNode->value = value;	
	return newNode; 
}

// insert at the beginning
void insert_at_head(struct linked_list *list, size_t value) {
	struct list_node *newNode = new_node(value);
	if(newNode == NULL){return;}
	newNode->next = list->head;	// connect to rest of linked list
	list->head = newNode;
	
}

// insert at the end
void insert_at_tail(struct linked_list *list, size_t value) {
	struct list_node *newNode = new_node(value);

	if(list->head == NULL){
		list->head = newNode;
		return;
	}
	struct list_node *currNode = list->head;
	while(currNode->next != NULL){
		currNode = currNode->next;	// move forward one
	}
	currNode->next = newNode; 
}

// remove from the beginning
size_t remove_from_head(struct linked_list *list) { 
	if(list->head == NULL){
		return 0;
	}
	struct list_node *oldNode = list->head;	// save old head
	size_t rtv = oldNode->value;
	list->head = oldNode->next;
	free(oldNode);
	
	return rtv; // completed properly 
}

// remove from the end
size_t remove_from_tail(struct linked_list *list) { 
	if(list->head == NULL){return 0;}

	// check for tail node.
	struct list_node *currNode = list->head;
	struct list_node *prevNode = NULL;
	while(currNode->next != NULL){
		prevNode = currNode;
		currNode = currNode->next;
	}
	size_t rtv = currNode->value;
	if(prevNode == NULL){
		list->head = NULL;
	}else{
		prevNode->next = NULL;
	}

	free(currNode);
	return rtv;
}

// free the linked list
void free_list(struct linked_list list) {
	while(list.head != NULL){
		struct list_node *temp = list.head;
		list.head = list.head->next;
		free(temp);
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
