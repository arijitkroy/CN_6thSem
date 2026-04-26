#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define IP "127.0.0.1"
#define PORT 15550

void main() {
	struct sockaddr_in server, client;
	int n, s, pid, slen = sizeof(server), clen = sizeof(client);
	char msg[512];
	bzero((char *)&server, slen);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(IP);
	server.sin_port = htons(PORT);
	s = socket(AF_INET, SOCK_DGRAM, 0);
	bind(s, (struct sockaddr *)&server, slen);
	while (1) {
		n = recvfrom(s, msg, 512, 0, (struct sockaddr *)&client, &clen);
		if (n <= 0) break;
		pid = fork();
		if (pid == 0) {
			sendto(s, msg, n, 0, (struct sockaddr *)&client, clen);
		}
	}
	close(s);
}
