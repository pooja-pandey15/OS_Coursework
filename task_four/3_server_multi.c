#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    printf("Print server waiting for clients on port 8080...\n");
    printf("(will handle 3 clients then stop)\n\n");

    for (int i = 1; i <= 3; i++) {
        int client_fd = accept(server_fd, NULL, NULL);
        printf("Client %d connected.\n", i);

        char buffer[100] = {0};
        read(client_fd, buffer, 100);
        printf("Client %d print job: %s\n", i, buffer);

        char reply[100];
        sprintf(reply, "Job %d received and queued.", i);
        send(client_fd, reply, strlen(reply), 0);

        close(client_fd);
        printf("Client %d handled.\n\n", i);
    }

    close(server_fd);
    printf("Server done, all 3 clients handled.\n");
    return 0;
}
