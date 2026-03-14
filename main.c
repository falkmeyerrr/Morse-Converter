#include <stdio.h>
#include <string.h>

#define ALPHABET_SIZE 26


int main() {
    char messagein[100];
    const char *morse_code[ALPHABET_SIZE] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",
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

    // Just for exe click
    char exit[2], comand = 'e';
    int flag = 0;
    while (exit) {
        if (flag == 1) {
            printf("\r\e[31m>>> Input error\e[0m\n");
        }
        if (!fgets(exit, sizeof(exit), stdin) != 70) {
            exit[strcspn(exit, "\n")] = 0;
        } else {break;}
    }


    return 0;
}
