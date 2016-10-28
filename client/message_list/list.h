#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Holds data to keep track of sent messages
struct message_node {
	char* message;
	int is_received;

	struct message_node* next;
	struct message_node* prev;
};

// Linked list of message nodes
struct message_list {
	struct message_node* head;
	struct message_node* tail;
};

// Pushes a message into the linked list
void pushMessage(struct message_list* list, char* message);

// Finds a message in the linked list. Returns the 
// 	message_node if found, or 0 if not found
struct message_node* findMessage(struct message_list* list, char* message);
