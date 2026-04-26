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
	int n, s, ns, clen = sizeof(client), ack = 0;
	char f;
	bzero((char *)&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(IP);
	server.sin_port = htons(S_PORT);
	s = socket(AF_INET, SOCK_STREAM, 0);
	bind(s, (struct sockaddr *)&server, sizeof(server));
	listen(s, 5);
	ns = accept(s, (struct sockaddr *)&client, &clen);
	while (1) {
		n = recv(ns, &f, sizeof(char), 0);
		if (n == 0) break;
		printf("Received frame:  %c\n", f);
		ack++;
		send(ns, &ack, sizeof(int), 0);
		printf("Sent ACK: %d\n", ack);
	}
	close(ns);
	close(s);
}
