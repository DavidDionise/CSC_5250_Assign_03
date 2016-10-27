#include <stdio.h>

#include "../util/util.h"

#define MAX_READ_LENGTH 2096

int main(int argc, char* argv[]) {
	if(argc < 2) {
		perror("Must include port number");
		exit(1);
	}

	int socket_fd;
	int port_number = atoi(argv[1]);
	char read_buffer[MAX_READ_LENGTH];
	char* r_str;

	struct sockaddr_in server_addr, client_addr;

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port_number);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	if((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("Error creating socket");
		exit(1);
	}

	if((bind(socket_fd, (const struct sockaddr *) &server_addr,
		(socklen_t)sizeof(server_addr))) < 0) {
		perror("Error binding");
		exit(1);
	}

	socklen_t client_addr_length = (socklen_t)sizeof(client_addr);

	puts("Server Starting");

	int len;
	while(1){
		if((len = recvfrom(socket_fd, read_buffer, MAX_READ_LENGTH, 0,
			(struct sockaddr *)&client_addr, &client_addr_length)) < 0) {
			perror("Error reading from client\n");
			exit(1);
		}
	
		printf("length = %i\n", len);
		printf("read_buffer = %s\n", read_buffer);
		r_str = processString(read_buffer, len - 1);
		printf("r_str = %s\n", r_str);

		if ((sendto(socket_fd, r_str, len, 0,
			(struct sockaddr *)&client_addr, client_addr_length)) < 0) {
			perror("Error writing to client\n");
			exit(1);
		}

		free(r_str);
		bzero(read_buffer, len);
	}

	close(socket_fd);
	return 0;
}
