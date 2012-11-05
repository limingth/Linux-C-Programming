
PORT = 8004
SERVER_FILES = server.c 
CLIENT_FILES = client.c 

all:
	gcc $(SERVER_FILES) -o server
	gcc $(CLIENT_FILES) -o client

s:
	./server $(PORT)

c:
	./client 192.168.211.2 $(PORT)

