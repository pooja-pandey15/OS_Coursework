#include <stdio.h>
#include <time.h>
#include <string.h>

void log_action(const char *action) {
    FILE *log = fopen("audit.log", "a");   // "a" = append, so old logs are not lost

    time_t now = time(NULL);
    char *timestamp = ctime(&now);
    timestamp[strlen(timestamp) - 1] = '\0';  // remove newline ctime adds

    fprintf(log, "[%s] %s\n", timestamp, action);
    fclose(log);
}

int main() {
    printf("Simulating file actions...\n\n");

    log_action("User pooja logged in");
    log_action("File secret_note.txt created");
    log_action("File secret_note.txt read");
    log_action("File secret_note.txt deleted");

    printf("Actions logged. Reading back audit.log:\n\n");

    FILE *log = fopen("audit.log", "r");
    char line[200];
    while (fgets(line, 200, log) != NULL) {
        printf("%s", line);
    }
    fclose(log);

    return 0;
}
