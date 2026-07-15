#include <stdio.h>
#include <sys/stat.h>

int main() {
    FILE *f = fopen("secret_note.txt", "w");
    fputs("This is private.\n", f);
    fclose(f);

    printf("File created.\n");

    // set permission: owner can read/write, group and others cannot access at all
    chmod("secret_note.txt", S_IRUSR | S_IWUSR);
    printf("Permission set: owner can read and write only.\n");

    // check what permissions it actually has now
    struct stat info;
    stat("secret_note.txt", &info);

    printf("\nPermission check:\n");
    printf("Owner read:  %s\n", (info.st_mode & S_IRUSR) ? "yes" : "no");
    printf("Owner write: %s\n", (info.st_mode & S_IWUSR) ? "yes" : "no");
    printf("Group read:  %s\n", (info.st_mode & S_IRGRP) ? "yes" : "no");
    printf("Others read: %s\n", (info.st_mode & S_IROTH) ? "yes" : "no");

    return 0;
}
