#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define IP "127.0.0.1"
#define PORT 15550

void main() {
	struct sockaddr_in server, client;
	int n, s, ns, pid, slen = sizeof(server), clen = sizeof(client);
	char msg[512];
	bzero((char *)&server, slen);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(IP);
	server.sin_port = htons(PORT);
	s = socket(AF_INET, SOCK_STREAM, 0);
	bind(s, (struct sockaddr *)&server, slen);
	listen(s, 5);
	while (1) {
		ns = accept(s, (struct sockaddr *)&client, &clen);
		pid = fork();
		if (pid == 0) {
			while (1) {
				n = recv(ns, msg, 512, 0);
				if (n <= 0) break;
				send(ns, msg, strlen(msg)+1, 0);
			}
		}
		else if (pid > 0) close(ns);
		else exit(0);
	}
	close(s);
}
