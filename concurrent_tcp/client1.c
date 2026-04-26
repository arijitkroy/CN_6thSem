#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define IP "127.0.0.1"
#define PORT 15550
#define C_PORT 15554

void main() {
	struct sockaddr_in server, client;
	int n, s, slen = sizeof(server);
	char msg[512];
	bzero((char *)&client, sizeof(client));
	client.sin_family = AF_INET;
	client.sin_addr.s_addr = inet_addr(IP);
	client.sin_port = htons(C_PORT);
	bzero((char *)&server, slen);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(IP);
	server.sin_port = htons(PORT);
	s = socket(AF_INET, SOCK_STREAM, 0);
	bind(s, (struct sockaddr *)&client, sizeof(client));
	connect(s, (struct sockaddr *)&server, sizeof(server));
	while (1) {
		printf("Enter message: ");
		scanf("%s", msg);
		if (strcmp(msg, "stop") == 0) break;
		send(s, msg, strlen(msg)+1, 0);
		memset(msg, 0x0, 512);
		recv(s, msg, 512, 0);
		printf("Response: %s\n", msg);
	}
	close(s);
}
