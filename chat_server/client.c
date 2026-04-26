// broadcast_client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 15550

int main() {
    int s;
    struct sockaddr_in server;
    char msg[512];

    s = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    connect(s, (struct sockaddr*)&server, sizeof(server));

    if (fork() == 0) {
        // receive messages
        while (1) {
            int n = recv(s, msg, sizeof(msg), 0);
            if (n > 0) {
                msg[n] = '\0';
                printf("\nOther: %s", msg);
            }
        }
    } else {
        // send messages
        while (1) {
            fgets(msg, sizeof(msg), stdin);
            send(s, msg, strlen(msg), 0);
        }
    }

    close(s);
    return 0;
}