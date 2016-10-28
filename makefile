TCP_client: 
	gcc util/util.h util/util.c client/TCP_client.c -o client/TCP_client	


UDP_client: 
	gcc util/util.h util/util.c client/message_list/list.h client/message_list/list.c client/UDP_client.c -o client/UDP_client	

TCP_server: 
	gcc util/util.h util/util.c server/TCP_server.c -o server/TCP_server -lnsl -lsocket -lresolv	

UDP_server: 
	gcc util/util.h util/util.c server/UDP_server.c -o server/UDP_server -lnsl -lsocket -lresolv		


