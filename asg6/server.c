#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <time.h>

#define IP "127.0.0.1"
#define S_PORT 15550

void main() {
	struct sockaddr_in client, server;
	int n, s, ns, clen = sizeof(client);
	char msg[512], err[] = "Invalid request!", *t;
	time_t t1;
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
			n = recv(ns, msg, 512, 0);
			if (n == 0) exit(0);
			if (strcmp(msg, "time") == 0) {
				t1 = time(NULL);
				t = ctime(&t1);
				send(ns, t, strlen(t)+1, 0);
			}
			else send(ns, err, strlen(err)+1, 0);
		}
		close(ns);
	}
	close(s);
}

