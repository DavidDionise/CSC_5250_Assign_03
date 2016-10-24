all: sockOptions utils main
	
sockOptions: 
	gcc -o sockOptions SocketOptions/NP.h SocketOptions/NP.c

utils: 
	gcc -o utils util/util.h util/util.c


