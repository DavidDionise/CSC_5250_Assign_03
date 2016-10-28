#include "list.h"

void pushMessage(struct message_list* list, char* message) {
	struct message_node* new_node = malloc(sizeof(struct message_node));
	new_node->message = message;
	new_node->is_received = 0;

	if(list->head == 0) {
		list->head = new_node;	
		list->tail = new_node;
		
		new_node->next = 0;
		new_node->prev = 0;
	}
	else if(list->head == list->tail){
		list->head->next = new_node;
		list->tail = new_node;
		
		new_node->next = 0;
		new_node->prev = list->head;
	}
	else {
		list->tail->next = new_node;

		new_node->prev = list->tail;
		list->tail = new_node;
		new_node->next = 0;
	}
}

struct message_node* findMessage(struct message_list * list, char* message) {
	struct message_node * current = 
		list->head;

	while(current) {
		if(strcmp(message, current->message) == 0) 
			return current;
		else
			current = current->next;
	}

	return 0;
}

