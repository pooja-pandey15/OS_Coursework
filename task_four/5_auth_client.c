#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    char username[20], password[20];
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    char login[50];
    sprintf(login, "%s:%s", username, password);

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);

    connect(sock, (struct sockaddr *)&server_address, sizeof(server_address));

    send(sock, login, strlen(login), 0);

    char buffer[100] = {0};
    read(sock, buffer, 100);
    printf("Server: %s\n", buffer);

    // only send a job if login succeeded
    if (strcmp(buffer, "Login OK. Send your print job.") == 0) {
        char *job = "Print 3 pages, report.pdf";
        send(sock, job, strlen(job), 0);

        char reply[100] = {0};
        read(sock, reply, 100);
        printf("Server: %s\n", reply);
    }

    close(sock);
    return 0;
}
