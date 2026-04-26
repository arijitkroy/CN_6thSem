#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define IP "127.0.0.1"
#define PORT 15550

void main() {
	struct sockaddr_in server, client;
	int n, s, slen = sizeof(server);
	char msg[512];
	bzero((char *)&server, slen);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(IP);
	server.sin_port = htons(PORT);
	s = socket(AF_INET, SOCK_DGRAM, 0);
	while (1) {
		printf("Enter message: ");
		scanf("%s", msg);
		if (strcmp(msg, "stop") == 0) break;
		sendto(s, msg, strlen(msg)+1, 0, (struct sockaddr *)&server, slen);
		memset(msg, 0x0, 512);
		n = recvfrom(s, msg, 512, 0, NULL, NULL);
		msg[n] = '\0';
		printf("Response: %s\n", msg);
	}
	close(s);
}
