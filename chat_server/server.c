// broadcast_server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 15550
#define MAX 10

int clients[MAX];
int count = 0;

// send message to all clients except sender
void broadcast(char *msg, int sender) {
    for (int i = 0; i < count; i++) {
        if (clients[i] != sender) {
            send(clients[i], msg, strlen(msg), 0);
        }
    }
}

int main() {
    int s, ns;
    struct sockaddr_in server, client;
    socklen_t clen = sizeof(client);
    char msg[512];

    s = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    bind(s, (struct sockaddr*)&server, sizeof(server));
    listen(s, 5);

    printf("Broadcast server started...\n");

    while (1) {
        ns = accept(s, (struct sockaddr*)&client, &clen);

        // add client
        clients[count++] = ns;

        if (fork() == 0) {
            while (1) {
                int n = recv(ns, msg, sizeof(msg), 0);
                if (n <= 0) break;

                msg[n] = '\0';
                printf("Client: %s", msg);

                broadcast(msg, ns);
            }

            close(ns);
            exit(0);
        }
    }

    close(s);
    return 0;
}