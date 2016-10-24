all:
	gcc -o sockOpts.o SocketOptions/NP.h SocketOptions/NP.c
	gcc -o utils.o util/util.h util/util.c
	gcc -o TCP_client sockOpts.o utils.o TCP_client

