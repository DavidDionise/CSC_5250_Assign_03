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

/*int main() {
	struct message_list list;

	list.head = 0;
	list.tail = 0;

	pushMessage(&list, "message1");
	pushMessage(&list, "message2");
	pushMessage(&list, "hey there");
	pushMessage(&list, "yooour kinda dumb");
	struct message_node * m;

	m = findMessage(&list, "hey there");
	
	printf("head = %s\n", list.head->message);
	printf("tail = %s\n", list.tail->message);
	if(m)
		printf("message = %s\n", m->message);
	else
		puts("no message");
	

	return 0;
}*/
