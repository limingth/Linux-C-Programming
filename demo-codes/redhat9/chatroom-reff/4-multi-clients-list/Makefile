
PORT = 8000
SERVER_FILES = server.c user_online.c  
CLIENT_FILES = client.c 
#CFLAGS = -Wall

SERVER = Server
CLIENT = Client

all:
	gcc $(CFLAGS) $(SERVER_FILES) -o $(SERVER)
	gcc $(CFLAGS) $(CLIENT_FILES) -o $(CLIENT) 
#	gcc $(CFLAGS) user_online.c -E -o test.i
#	gcc $(CFLAGS) user_online.c -o test

clean:
	rm $(SERVER) $(CLIENT)

s:
	./$(SERVER) $(PORT)

c:
	./$(CLIENT) 192.168.211.2 $(PORT)

