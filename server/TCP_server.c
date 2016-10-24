
#include <stdio.h>
#include <sys/wait.h>

#include "../SocketOptions/NP.h"
#include "../util/util.h"

#define MAX_READ_LENGTH 2096

char* processString(char* str, int length);

int main(int argc, char* argv[]) {
	
	int socket_fd, socket_fd_a;
	int port_number = atoi(argv[1]);
	char read_buffer[MAX_READ_LENGTH];
	pid_t pid;

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
		
		pid = fork();

		// Child process
		if(pid == 0) {
			char* r_str = processString(read_buffer, len);

			if ((write(socket_fd_a, r_str, len)) < 0) {
				perror("Error writing to client\n");
				exit(1);
			}
			exit(0);
		}

		// Parent process
		else if(pid > 0){
			if(wait(0) == -1) {
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
	close(socket_fd_a);
	return 0;
}

char* processString(char* str, int length) {
	if(str[0] == '^') 
		str = reverseCase(&str[1], length);

	char* reversed_str = reverseString(str, length);

	return reversed_str;
}
