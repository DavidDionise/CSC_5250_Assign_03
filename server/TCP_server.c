
#include <stdio.h>

#include "../SocketOptions/NP.h"
#include "../util/util.h"

#define MAX_READ_LENGTH 2096

char* processString(char* str, int length);

int main(int argc, char* argv[]) {
	
	int socket_fd, socket_fd_a;
	int port_number = atoi(argv[1]);
	char read_buffer[MAX_READ_LENGTH];

	struct sockaddr_in  server_addr, client_addr;

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port_number);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	socket_fd = Socket(AF_INET, SOCK_STREAM, 0);

	Bind(socket_fd, (const struct sockaddr *) &server_addr,
		(socklen_t)sizeof(server_addr));	

	int client_addr_length = sizeof(client_addr);

	puts("Server Starting");

	Listen(socket_fd, 10);
	socket_fd_a = Accept(socket_fd, (struct sockaddr *)&client_addr, 
		(socklen_t*)&client_addr_length);

	int len;
	while(1){
		if((len = read(socket_fd_a, read_buffer, MAX_READ_LENGTH)) < 0) {
			perror("Error reading from client\n");
			exit(1);
		}
		if ((write(socket_fd_a, read_buffer, len)) < 0) {
			perror("Error writing to client\n");
			exit(1);
		}

		bzero(read_buffer, len);
	}

	close(socket_fd);
	close(socket_fd_a);
	return 0;
}

char* processString(char* str) {
	char * reversed_str = reverseString(str);



}
