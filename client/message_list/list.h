#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct message_node {
	char* message;
	int is_received;

	struct message_node* next;
	struct message_node* prev;
};

struct message_list {
	struct message_node* head;
	struct message_node* tail;
};

void pushMessage(struct message_list* list, char* message);

struct message_node* findMessage(struct message_list* list, char* message);
