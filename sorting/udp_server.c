#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <time.h>

#define S_IP "127.0.0.1"
#define S_PORT 15550

void bubble(int arr[], int n) {
	int i, j, temp;
	for (i = 0; i < n - 1; i++) {
		for (j = 0; j < n - i - 1; j++) {
			if (arr[j+1] < arr[j]) {
				temp = arr[j+1];
				arr[j+1] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

int main() {
	struct sockaddr_in client, server;
	int s, clen = sizeof(client), slen = sizeof(server), arr[512], n;
	char msg[512], *t;
	time_t t1;
	bzero((char *)&server, slen);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(S_IP);
	server.sin_port = htons(S_PORT);
	s = socket(AF_INET, SOCK_DGRAM, 0);
	bind(s, (struct sockaddr *)&server, slen);
	while (strcmp(msg, "stop")) {
		n = recvfrom(s, arr, 512, 0, (struct sockaddr *)&client, &clen);
		bubble(arr, n / sizeof(int));
		sendto(s, arr, n, 0, (struct sockaddr *)&client, clen);
	}
	close(s);
	return 0;
}
