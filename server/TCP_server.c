
#include <stdio.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <strings.h>

#include "../util/util.h"

#define MAX_READ_LENGTH 2096

char* processString(char* str, int length);

int main(int argc, char* argv[]) {
	
	int socket_fd, new_socket;
	int port_number = atoi(argv[1]);
	char read_buffer[MAX_READ_LENGTH];
	pid_t pid;

	struct sockaddr_in  server_addr, client_addr;

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port_number);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	if((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Error creating socket");
		exit(1);
	}

	if((bind(socket_fd, (const struct sockaddr *) &server_addr,
		(socklen_t)sizeof(server_addr))) < 0) {
		perror("Error binding");
		exit(1);
	}	

	int client_addr_length = sizeof(client_addr);

	puts("Server Starting");

	if(listen(socket_fd, 10) < 0) {
		perror("Error initializing listen");
		exit(1);
	}
	
	int len;
	while(1){
		if ((new_socket = accept(socket_fd, (struct sockaddr *)&client_addr, 
		(socklen_t*)&client_addr_length)) < 0) {
			perror("Error accepting client");
			exit(1);
		}

		if((len = read(new_socket, read_buffer, MAX_READ_LENGTH)) < 0) {
			perror("Error reading from client\n");
			exit(1);
		}
		
		pid = fork();

		// Child process
		if(pid == 0) {
			char* r_str = processString(read_buffer, len - 1);

			if ((write(new_socket, r_str, len)) < 0) {
				perror("Error writing to client\n");
				exit(1);
			}
			close(new_socket);
			exit(0);
		}

		// Parent process
		else if(pid > 0){
			if(waitpid(pid, 0, 0) == -1) {
				perror("Error wating for child process. Exited with status");
				exit(1);
			}
		}
		
		// Error forking
		else 
			perror("Error forking new process. Exited with status");

		bzero(read_buffer, len);
	}

	close(socket_fd);
	close(new_socket);
	return 0;
}

char* processString(char* str, int length) {
	printf("str = %s\n", str);
	if(str[0] == '^') {
		puts("in if");
		str = reverseCase(&str[1], length);
		printf("str = + %s\n", str);
	}

	char* reversed_str = reverseString(str, length);
	return reversed_str;
}
