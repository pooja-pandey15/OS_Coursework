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

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    printf("Print server waiting for a client on port 8080...\n");

    int client_fd = accept(server_fd, NULL, NULL);
    printf("Client connected.\n");

    char buffer[100] = {0};
    read(client_fd, buffer, 100);
    printf("Received print job: %s\n", buffer);

    char *reply = "Print job received and queued.";
    send(client_fd, reply, strlen(reply), 0);

    close(client_fd);
    close(server_fd);
    return 0;
}
