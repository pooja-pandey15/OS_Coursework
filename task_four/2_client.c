#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);

    connect(sock, (struct sockaddr *)&server_address, sizeof(server_address));

    char *message = "Print 5 pages, document.pdf";
    send(sock, message, strlen(message), 0);
    printf("Sent print job to server.\n");

    char buffer[100] = {0};
    read(sock, buffer, 100);
    printf("Server replied: %s\n", buffer);

    close(sock);
    return 0;
}

