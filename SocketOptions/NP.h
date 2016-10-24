#ifndef NP_H
#define NP_H

/* Most of this code came from the Unix Network Programming book.
 * The code was tweaked as needed.*/
enum {MAXLINE = 4096, LISTENQ = 100};
#include <stdarg.h> 	//Needed for va_list
#include <errno.h> 	    //Needed to use errno
#include <strings.h> 	//needed for the bzero function
#include <string.h>
#include <stdio.h>      //standard C i/o facilities
#include <stdlib.h>     //needed for atoi()
#include <unistd.h>     //Unix System Calls
#include <sys/types.h>  //system data type definitions
#include <sys/socket.h> //socket specific definitions
#include <netdb.h>
#include <netinet/in.h> //INET constants and stuff
#include <arpa/inet.h>  //IP address conversion stuff
#include <stdbool.h>	//Needed for booleans 
#include <sys/wait.h>   //Needed for waitpid
#include <signal.h>		//Needed for signal handling 
#include <syslog.h>    // Needed for syslog()


/************* Socket Wrappers *************************************/

//socket creation
int Socket(int family, int type, int protocol);

//connect
void Connect(int fd, const struct sockaddr *sa, socklen_t salen);

//close
void Close(int fd);

//accept
int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr);

//bind
void Bind(int fd, const struct sockaddr *sa, socklen_t salen);

//listen
void Listen(int fd, int backlog);

/************* I/O Wrappers ******************************************/

//write
void Writen(int fd, void *ptr, size_t nbytes);

//readline wrapper
ssize_t Readline(int fd, void *ptr, size_t maxlen);

// Read until delim is read
size_t ReadUntil(int fd, void *buf, char delim);

//recvfrom wrapper
ssize_t	 Recvfrom(int, void *, size_t, int, struct sockaddr *, socklen_t *);

//write
void Write(int fd, void *ptr, size_t nbytes);

//sendto wrapper
void Sendto(int, const void *, size_t, int, const struct sockaddr *, socklen_t);


//fclose
void Fclosee(FILE *fp);

//fdopen
FILE * Fdopen(int fd, const char *type);

//fgets
char * Fgets(char *ptr, int n, FILE *stream);

//fopen
FILE * Fopen(const char *filename, const char *mode);

//fputs
void Fputs(const char *ptr, FILE *stream);

/*********** Address Conversion **************************************/

//inet_pton wrapper
void Inet_pton(int family, const char *strptr, void *addrptr);

//inet_ntop wrapper
void Inet_ntop(int family, const void *addrptr, char *strptr, size_t len);

/************* Error Handling ************************************/

// Fatal error related to system call. Print message and terminate.
void err_sys(const char *fmt, ...);

//Fatal error unrelated to system call
void err_quit(const char *fmt, ...);

//Nonfatal error related to system call. Print message and return.
void err_ret(const char *fmt, ...);

/************* Signal Handling *************************************/
/* Define a prototype for signal handlers */
typedef	void Sigfunc(int);

//Wrapper around the signal function
Sigfunc *Signal(int signo, Sigfunc *func); 

/*********************** Other ***************************************/

//Fork wrapper
pid_t Fork(void);

#endif
