#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define IP "127.0.0.1"
#define S_PORT 15550

void main() {
	struct sockaddr_in client, server;
	int n, s, ns, clen = sizeof(client);
	char msg[512];
	bzero((char *)&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(IP);
	server.sin_port = htons(S_PORT);
	s = socket(AF_INET, SOCK_STREAM, 0);
	bind(s, (struct sockaddr *)&server, sizeof(server));
	listen(s, 5);
	while (1) {
		ns = accept(s, (struct sockaddr *)&client, &clen);
		while (1) {
			memset(msg, 0x0, 512);
			n = recv(ns, msg, 512, 0);
			if (n == 0) exit(0);
			printf("[CLIENT_IP: %s | CLIENT_PORT: %u]: %s\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port), msg);
		}
		close(ns);
	}
	close(s);
}
