
#include <unistd.h>     
#include <sys/types.h>  
#include <sys/socket.h> 
#include <netdb.h>
#include <netinet/in.h> 
#include <arpa/inet.h>  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Returns an IP address from a domain name 
//	or IP address
char* getIP(char* domain_name);

// Reads entire line until \n character
char* getLine();

// Reverses characters in a string
char* reverseString(char* str, int length);

// Reverses case for each character in a string
char* reverseCase(char* str, int length);

// Processes a string based on the input
char* processString(char* str, int length);
