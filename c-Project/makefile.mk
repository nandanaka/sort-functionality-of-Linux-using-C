a.out : client.o serever.o
	gcc -o a.out client.o server.o
client.o : client.c
	gcc -c client.c
server.o : server.c server.h
	gcc -c server.c
