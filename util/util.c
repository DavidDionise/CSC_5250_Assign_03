
#include "util.h"


char* getIP(char* domain_name) {
	puts("starting getIP");
	struct addrinfo res;
	struct addrinfo *res_ptr = &res;
	int error_val;

	memset(&res, 0, sizeof(res));
	
	if((error_val = getaddrinfo(domain_name, 0, 0, &res_ptr)) == 0) {
		struct sockaddr_in *sa = (struct sockaddr_in *) res_ptr->ai_addr;
		socklen_t sa_len = (socklen_t) sizeof(*sa);

		puts("ending getIP");
		return inet_ntoa(sa->sin_addr);
	}
	else {
		printf("%s", gai_strerror(error_val));
		exit(1);
	}
}

char* getLine() {
	int length = 10;
	int count = 0;
	char* buffer = (char*)malloc(sizeof(char) * length);
	char* buf_ptr = &buffer[0];
	char c;

	*buf_ptr = '\0';
	
	while((c = getchar()) != '\n') {
		if(count >= (length - 1)) {
			length += 10;
			buffer = (char*)realloc(buffer, length);
		}

		++count;
		*buf_ptr = c;
		*(++buf_ptr) = '\0';
	}

	return buffer;
}

char* reverseString(char* str, int length) {
	char* str_ptr = &str[length - 1];	

	char* reversed_str = (char*)malloc(sizeof(char) * (length + 1));
	char* r_str_ptr = &reversed_str[0];
	
	int i;
	for(i = 0; i < length + 1; i++) {
		*r_str_ptr++ = *str_ptr;
		str_ptr--;
	}

	*r_str_ptr = '\0';

	return reversed_str;
}

char* reverseCase(char* str, int length) {
	char* str_ptr = &str[0];	

	char* reversed_case_str = (char*)malloc(sizeof(char) * (length + 1));
	char* r_str_ptr = &reversed_case_str[0];

	int i;
	for(i = 0; i < length; i++) {
		int cast = (int)*str_ptr;

		if(cast >= 97 && cast <= 122) 
			*r_str_ptr = (char)(cast - 32);
		else if(cast >= 65 && cast <= 90) 
			*r_str_ptr = (char)(cast + 32);
		else
			*r_str_ptr = *str_ptr;
	
		str_ptr++;
		r_str_ptr++;
	}

	*r_str_ptr = '\0';

	return reversed_case_str;
}

char* processString(char* str, int length) {
	char* reversed_case_str;
	char* reversed_str;
	if(str[0] == '^') {
		length--; 	// Decrement to account for carot character
		reversed_case_str = reverseCase(&str[1], length);
		reversed_str = reverseString(reversed_case_str, length);
	}
	else
		reversed_str = reverseString(str, length);
 
	return reversed_str;
}

/*int main() {
	char* str = "hey there";
	char* new_str = reverseString(str, 9);
	printf("new str = %s\n", new_str);
}*/

