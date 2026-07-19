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

    printf("Secure print server waiting for a client...\n");

    int client_fd = accept(server_fd, NULL, NULL);
    printf("Client connected.\n");

    char login[100] = {0};
    read(client_fd, login, 100);
    printf("Login attempt: %s\n", login);

    if (strcmp(login, "pooja:1234") == 0) {
        char *reply = "Login OK. Send your print job.";
        send(client_fd, reply, strlen(reply), 0);

        char job[100] = {0};
        read(client_fd, job, 100);
        printf("Print job: %s\n", job);

        char *done = "Print job received and queued.";
        send(client_fd, done, strlen(done), 0);
    } else {
        char *reply = "Login failed. Connection closed.";
        send(client_fd, reply, strlen(reply), 0);
        printf("Login failed, closing connection.\n");
    }

    close(client_fd);
    close(server_fd);
    return 0;
}
