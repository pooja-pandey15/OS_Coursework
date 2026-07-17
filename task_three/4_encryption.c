#include <stdio.h>
#include <string.h>

#define KEY 'K'   // simple key used to scramble the text

void encrypt_decrypt(char *text) {
    for (int i = 0; text[i] != '\0'; i++) {
        text[i] = text[i] ^ KEY;   // XOR each character with the key
    }
}

int main() {
    char text[100];

    printf("Enter sensitive note: ");
    fgets(text, 100, stdin);
    text[strcspn(text, "\n")] = '\0';   // remove newline

    printf("Original:  %s\n", text);

    encrypt_decrypt(text);
    printf("Encrypted: %s\n", text);

    encrypt_decrypt(text);   // XOR again with same key reverses it
    printf("Decrypted: %s\n", text);

    return 0;
}
