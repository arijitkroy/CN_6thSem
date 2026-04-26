#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define S_IP "127.0.0.1"
#define S_PORT 15550

int main() {
	struct sockaddr_in client, server;
	int s, clen = sizeof(client), slen = sizeof(server), n, i, arr[512];
	char msg[512];
	bzero((char *)&server, slen);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(S_IP);
	server.sin_port = htons(S_PORT);
	s = socket(AF_INET, SOCK_DGRAM, 0);
	while (strcmp(msg, "stop")) {
		printf("Enter size of array: ");
		scanf("%d", &n);
		printf("Enter elements: ");
		for (i = 0; i < n; i++) scanf("%d", &arr[i]);
		sendto(s, arr, n * sizeof(int), 0, (struct sockaddr *)&server, slen);
		recvfrom(s, arr, 512, 0, (struct sockaddr *)&server, &slen);
		printf("Sorted elements: ");
		for (i = 0; i < n; i++) printf("%d ", arr[i]);
		printf("\n");
	}
	close(s);
	return 0;
}
