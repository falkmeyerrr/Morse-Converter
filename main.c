#include <stdio.h>
#include <string.h>

#define ALPHABET_SIZE 26

void clear_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    char messagein[100];
    const char *morse_code[ALPHABET_SIZE] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",
                              ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",
                              "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};
    const char *morse_code_american[ALPHABET_SIZE] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",
                              ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",
                              "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};
    printf("What is the message you want to encode?\n");


    /* Input message */
    if (!fgets(messagein, sizeof(messagein), stdin)) {
        printf("\e[31m>>> Input error\e[0m\n");
        return 1;
    }
    messagein[strcspn(messagein, "\n")] = 0;


    /* Convertation I */
    for (int i = 0; messagein[i] != '\0'; i++) {
        
        char c = messagein[i];

        if (c >= 'A' && c <= 'Z') {  // Convert to the lover register
            int idx = c - 'A';
            printf("\e[32m%s\e[0m/", morse_code[idx]);

        } else if (c >= 'a' && c <= 'z') {  // Basic convert
            int idx = c - 'a';
            printf("\e[32m%s\e[0m/", morse_code[idx]);

        } else if (c == ' ') {  /* 2 spaces between words (Morse standart)*/
            printf("  ");
        }
        else {  /* Unknown symbol detection */
            printf("%c ", c);
        }
    }
    printf("\n");

    printf("Press \"Enter\" to exit: ");
    clear_input();

    return 0;
}
