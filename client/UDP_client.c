#include <arpa/inet.h>
#include <netinet/in.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/time.h>

#include "../util/util.h"
#include "./message_list/list.h"

#define MAX_READ_LENGTH 2048

int main(int argc, char* argv[]) {
	if (argc < 3) {
		perror("Missing hostname and/or port number\n");
		exit(1);
	}

	int socket_fd;
	int port_number = atoi(argv[2]);
	struct sockaddr_in server_addr;
	socklen_t server_addr_size;	

	char read_buffer[MAX_READ_LENGTH];
	char* message;
	int length, read_length;

	struct timeval timeout;
	timeout.tv_sec = 5;
	
	// Linked list used to keep track of messages
	// that were not successfully sent
	struct message_list m_list;
	m_list.head = 0;
	m_list.tail = 0;
	struct message_node* m_node;

	int received = 0;	// Bool flag to keep track of 
						//	whether or not a message has 
						//	been received


	socket_fd = socket(AF_INET, SOCK_DGRAM, 0);	

	if(setsockopt(socket_fd, SOL_SOCKET, SO_RCVTIMEO,
		&timeout, (socklen_t)sizeof(timeout)) < 0) {
		perror("Error setting socket options");
		exit(1);
	}

	// Initialize socket address
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port_number);

	if(inet_aton(getIP(argv[1]), &server_addr.sin_addr.s_addr) == 0) {
		perror("Error initializing server address\n");
		exit(1);
	}

	while(1) {
		puts("Enter a message : ");
		message = getLine();

		// End
		if(strcmp(message, "--") == 0)
			break;

		length = strlen(message);
		server_addr_size = (socklen_t)sizeof(server_addr);	
		if(sendto(socket_fd, message, length + 1, 0, (const struct sockaddr*)&server_addr, 	
			server_addr_size) < 0) {
			perror("Error sending message to server");
			exit(1);
		}
		while(!received) {
			if((read_length = recvfrom(socket_fd, read_buffer, length + 1, 0,
				(const struct sockaddr*)&server_addr, &server_addr_size)) < 0) {
				// Timeout signal
				if(errno == EAGAIN) {
					m_node = findMessage(&m_list, message);
					if(!m_node) 
						pushMessage(&m_list, message); 
			
					printf("Resending %s\n", message);
					if(sendto(socket_fd, message, length + 1, 0, (const struct sockaddr*)&server_addr, 	
						server_addr_size) < 0) {
						perror("Error sending message to server");
						exit(1);
					}

					continue; // Go to top of while
				}
				else {
					perror("Error receiving from server");
					exit(1);
				}
			}
			else {
				received = 1;
				free(message);
				m_node = findMessage(&m_list, read_buffer);
		
				if(m_node) {
					if(m_node->is_received) {				// Message in read_buffer has already been
						bzero(read_buffer, read_length);	//	read received by the client
						continue;				
					}
					else {
						m_node->is_received = 1;	// Message has not been received, mark the message
					}
				}
			}
		}		
		received = 0; // Reset flag

		// Printing message from server
		printf("%s\n", read_buffer);
		bzero(&read_buffer, MAX_READ_LENGTH); 
	}

	puts("Ending communication");

	free(message);
	close(socket_fd);

	return 0;
}


