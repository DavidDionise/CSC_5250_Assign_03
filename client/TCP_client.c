#include <arpa/inet.h>
#include <netinet/in.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>

#include <errno.h>
#include <math.h>
#include <netdb.h>

#include "../SocketOptions/NP.h"

void latency(char array[], int length, int fd, 
	float * average, float * min, float * max);

int main(int argc, char* argv[]) {

	if (argc < 3) {
		perror("Missing hostname and/or port number\n");
		exit(1);
	}

	int socket_fd;
	int port_number;
	struct sockaddr_in server_addr;

	socket_fd = Socket(AF_INET, SOCK_STREAM, 0);	
	port_number = atoi(argv[2]);

	// Initialize socket address
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port_number);
	
	if(inet_aton(getIP(argv[1]), &server_addr.sin_addr.s_addr) == 0) {
		perror("Error initializing server address\n");
		exit(1);
	}

	// Connect socket
	Connect(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));

	// Initialize data to send
	char byte_array_1[1] = {0x00};
	char byte_array_100[100] = {[0 ... 99] = 0x00};
	char byte_array_200[200] = {[0 ... 199] = 0x00};
	char byte_array_300[300] = {[0 ... 299] = 0x00};
	char byte_array_400[400] = {[0 ... 399] = 0x00};
	char byte_array_500[500] = {[0 ... 499] = 0x00};
	char byte_array_600[600] = {[0 ... 599] = 0x00};
	char byte_array_700[700] = {[0 ... 699] = 0x00};
	char byte_array_800[800] = {[0 ... 799] = 0x00};
	char byte_array_900[900] = {[0 ... 899] = 0x00};
	char byte_array_1000[1000] = {[0 ... 999] = 0x00};

	

	// Send message
	puts("\n");
	float average, min, max;

	latency(byte_array_1, 1, socket_fd, &average, &min, &max);
	printf("*** RTT for 1 Byte ***\n");
	printf("average = %.3f\n", average);
	printf("min = %.3f\n", min);
	printf("max = %.3f\n\n", max);

	latency(byte_array_100, 100, socket_fd, &average, &min, &max);
	printf("*** RTT for 100 Bytes ***\n");
	printf("average = %.3f\n", average);
	printf("min = %.3f\n", min);
	printf("max = %.3f\n\n", max);

	latency(byte_array_200, 200, socket_fd, &average, &min, &max);
	printf("*** RTT for 200 Bytes ***\n");
	printf("average = %.3f\n", average);
	printf("min = %.3f\n", min);
	printf("max = %.3f\n\n", max);

	latency(byte_array_300, 300, socket_fd, &average, &min, &max);
	printf("*** RTT for 300 Bytes ***\n");
	printf("average = %.3f\n", average);
	printf("min = %.3f\n", min);
	printf("max = %.3f\n\n", max);

	latency(byte_array_400, 400, socket_fd, &average, &min, &max);
	printf("*** RTT for 400 Bytes ***\n");
	printf("average = %.3f\n", average);
	printf("min = %.3f\n", min);
	printf("max = %.3f\n\n", max);

	latency(byte_array_500, 500, socket_fd, &average, &min, &max);
	printf("*** RTT for 500 Bytes ***\n");
	printf("average = %.3f\n", average);
	printf("min = %.3f\n", min);
	printf("max = %.3f\n\n", max);

	latency(byte_array_600, 600, socket_fd, &average, &min, &max);
	printf("*** RTT for 600 Bytes ***\n");
	printf("average = %.3f\n", average);
	printf("min = %.3f\n", min);
	printf("max = %.3f\n\n", max);

	latency(byte_array_700, 700, socket_fd, &average, &min, &max);
	printf("*** RTT for 700 Bytes ***\n");
	printf("average = %.3f\n", average);
	printf("min = %.3f\n", min);
	printf("max = %.3f\n\n", max);

	latency(byte_array_800, 800, socket_fd, &average, &min, &max);
	printf("*** RTT for 800 Bytes ***\n");
	printf("average = %.3f\n", average);
	printf("min = %.3f\n", min);
	printf("max = %.3f\n\n", max);

	latency(byte_array_900, 900, socket_fd, &average, &min, &max);
	printf("*** RTT for 900 Bytes ***\n");
	printf("average = %.3f\n", average);
	printf("min = %.3f\n", min);
	printf("max = %.3f\n\n", max);

	latency(byte_array_1000, 1000, socket_fd, &average, &min, &max);
	printf("*** RTT for 1000 Bytes ***\n");
	printf("average = %.3f\n", average);
	printf("min = %.3f\n", min);
	printf("max = %.3f\n\n", max);

	close(socket_fd);
	return 0;
}

void latency(char array[], int length, int fd, 
	float * average, float * min, float * max) {

	struct timespec begin;
	struct timespec end;

	begin.tv_nsec = 0;
	end.tv_nsec = 0;

	float difference;
	*min = 0;
	*max = 0;

	char buffer[length];
	bzero(buffer, length);

	int i;
	float sum = 0;
	for(i = 0; i < 100; i++) {
		clock_settime(CLOCK_REALTIME, &begin);

		if(write(fd, array, length) < 0) {
			perror("Error wrting to server");
			exit(1);
		}
		if(read(fd, buffer, length) < 0) {
			perror("Error reading from server");
			exit(1);
		}

		clock_gettime(CLOCK_REALTIME, &end);

		difference = (float)(end.tv_nsec - begin.tv_nsec) / 1000000;
		// Check for min and max
		if(*min == 0 || difference < *min)
			*min = difference;
		if(difference > *max)
			*max = difference;
		
		sum += difference;
		bzero(buffer, length);
	}

	*average = sum / 100;
}
