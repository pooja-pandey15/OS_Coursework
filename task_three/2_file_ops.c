#include <stdio.h>

int main() {
    FILE *f;
    char text[100];

    // create and write
    f = fopen("note.txt", "w");
    printf("Enter a note: ");
    fgets(text, 100, stdin);
    fputs(text, f);
    fclose(f);
    printf("Note saved.\n\n");

    // read
    f = fopen("note.txt", "r");
    fgets(text, 100, f);
    printf("Note content: %s\n", text);
    fclose(f);

    // delete
    if (remove("note.txt") == 0) {
        printf("Note deleted.\n");
    } else {
        printf("Could not delete note.\n");
    }

    return 0;
}

