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

#include "../util/util.h"

#define MAX_READ_LENGTH 2048

int main(int argc, char* argv[]) {
	if (argc < 3) {
		perror("Missing hostname and/or port number\n");
		exit(1);
	}

	int socket_fd;
	int port_number;
	struct sockaddr_in server_addr;
	char read_buffer[MAX_READ_LENGTH];
	
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);	
	port_number = atoi(argv[2]);

	// Initialize socket address
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port_number);
	
	if(inet_aton(getIP(argv[1]), &server_addr.sin_addr.s_addr) == 0) {
		perror("Error initializing server address\n");
		exit(1);
	}

	// Connect socket
	connect(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));

	puts("Enter a message : ");
	char* message = getLine();

	while(strcmp(message, "--")) {
		int length = strlen(message);
		int read_length;

		if((write(socket_fd, message, length + 1)) < 0) {
			perror("Error writing to server.");
			exit(1);
		}

		if((read_length = read(socket_fd, read_buffer, length)) < 0) {
			perror("Error reading from server.");
			exit(1);
		}

		printf("%s\n", read_buffer);
		bzero(read_buffer, read_length); 
	}

	close(socket_fd);
	return 0;
}


