#include <stdio.h>
#include <string.h>

int main() {
    char username[20];
    char password[20];

    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if (strcmp(username, "pooja") == 0 && strcmp(password, "1234") == 0) {
        printf("Login successful. Welcome %s.\n", username);
    } else {
        printf("Login failed. Wrong username or password.\n");
    }

    return 0;
}
