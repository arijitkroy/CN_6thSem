#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define IP "127.0.0.1"
#define C_PORT 15555
#define S_PORT 15550
#define WS 2

void main() {
	struct sockaddr_in client, server;
	char msg[] = "IMPORTANT_MESSAGE";
	int s, i, ack, frames, counter = 0, total = strlen(msg);
	bzero((char *)&client, sizeof(client));
	client.sin_family = AF_INET;
	client.sin_addr.s_addr = inet_addr(IP);
	client.sin_port = htons(C_PORT);
	bzero((char *)&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(IP);
	server.sin_port = htons(S_PORT);
	s = socket(AF_INET, SOCK_STREAM, 0);
	bind(s, (struct sockaddr *)&client, sizeof(client));
	connect(s, (struct sockaddr *)&server, sizeof(server));
	while (counter < total) {
		frames = 0;
		for (i = counter; i < WS + counter && i < total; i++) {
			printf("Sending frame: %c\n", msg[i]);
			send(s, &msg[i], sizeof(char), 0);
			frames ++;
		}
		for (i = 0; i < frames; i++) {
			recv(s, &ack, sizeof(int), 0);
			printf("Received Ack: %d\n", ack);
			counter = ack;
		}
		printf("----- Sliding window to index: %d -----\n", counter);
	}
	close(s);
}
