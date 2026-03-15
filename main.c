#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26
#define MAX_MESSAGE_LEN 100
#define ANSI_RED_COL     "\x1b[31m"
#define ANSI_GREEN_COL   "\x1b[32m"
#define ANSI_BLUE_COL    "\x1b[34m"
#define ANSI_COL_RESET   "\x1b[0m"


/* Internarional Standart */
static const char *morse_code[ALPHABET_SIZE] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",
                              ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",
                              "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};
static const char *mc_digits[10] = {"-----", ".----", "..---",
                                 "...--", "....-", ".....",
                                 "-....", "--...", "---..",
                                 "----."};
/* American Standart */
static const char *morse_code_american[ALPHABET_SIZE] = {".-", "-...", ".. .", "-..", ".", ".-.", "--.", "....", "..",
                              "-.-.", "-.-", "____", "--", "-.", ". .", ".....", "..-.", ". ..",
                              "...", "-", "..-", "...-", ".--", ".-..", ".. ..", "... ."};
static const char *mc_digits_american[10] = {".--.", "..-..", "...-.",
                                          "....-", "---", "......",
                                          "--..", "-....", "-..-", "_____"};

typedef enum {
    STANDART_INTERNATIONAL,
    STANDART_AMERICAN,
    STANDART_UNKNOWN
} MorseStandart;

void clean_output() {
    int c;
    while ((c = getchar()) != '\n' && (c != EOF));
}

MorseStandart get_morse_standart() {
    char choice[11];

    printf("Do you prefer "ANSI_BLUE_COL"International (I)"ANSI_COL_RESET
           " or "ANSI_RED_COL"American (A)"ANSI_COL_RESET" standart?\n>>> ");
    if (!fgets(choice, sizeof(choice), stdin)) {
        return STANDART_UNKNOWN;
    }

    /* Lower Register */
    for (int i = 0; choice[i]; i++) {
        choice[i] = tolower(choice[i]);
    }
    choice[strcspn(choice, "\n")] = 0;
    choice[strcspn(choice, " ")] = 0;

    if ((strchr(choice, 'i') != NULL)) return STANDART_INTERNATIONAL;
    if ((strchr(choice, 'a') != NULL)) return STANDART_AMERICAN;

    return STANDART_UNKNOWN;
}

bool get_message(char *message, int max_len) {
    printf("What is the message you want to encode?\n>>> ");
    
    if (!fgets(message, max_len, stdin)) {
        printf(ANSI_RED_COL">>> Input Error"ANSI_COL_RESET"\n");
        return false;
    }
    
    message[strcspn(message, "\n")] = 0;
    return true;
}

void international_encoder(char c) {
    if (c >= 'A' && c <= 'Z') {  // Convert to the lover register
        int idx = c - 'A';
        printf(ANSI_GREEN_COL"%s"ANSI_COL_RESET"/", morse_code[idx]);

    } else if (c >= 'a' && c <= 'z') {  // Basic convert
        int idx = c - 'a';
        printf(ANSI_GREEN_COL"%s"ANSI_COL_RESET"/", morse_code[idx]);

    } else if (c >= '0' && c <= '9'){
        int idx = c - '0';
        printf("%s/", mc_digits[idx]);
    }
    else if (c == '@') {
        printf(ANSI_RED_COL" .--.-. "ANSI_COL_RESET);
    } 
    else if (c == ' ') {  /* 2 spaces between words (Morse standart)*/
        printf("  ");
    }
    else {  /* Unknown symbol detection */
        printf("%c", c);
    }
}

void american_encoder(char c) {
    if (c >= 'A' && c <= 'Z') {  // Convert to the lover register
        int idx = c - 'A';
        printf(ANSI_GREEN_COL"%s"ANSI_COL_RESET"/", morse_code_american[idx]);

    } else if (c >= 'a' && c <= 'z') {  // Basic convert
        int idx = c - 'a';
        printf(ANSI_GREEN_COL"%s"ANSI_COL_RESET"/", morse_code_american[idx]);

    } else if (c >= '0' && c <= '9'){
        int idx = c - '0';
        printf("%s/", mc_digits_american[idx]);
    }
    else if (c == ' ') {  /* 2 spaces between words (Morse standart)*/
        printf("  ");
    }
    else {  /* Unknown symbol detection */
        printf("%c", c);
    }
}

void encode_message(const char *message, MorseStandart standart) {
    for (int i = 0; message[i] != '\0'; i++) {
        if (standart == STANDART_INTERNATIONAL) {
            international_encoder(message[i]);
        } else {
            american_encoder(message[i]);
        }
    }
    printf("\n");
}

int main() {
    char message[100];

    MorseStandart standart = get_morse_standart();

    if (standart == STANDART_UNKNOWN) {
        printf(ANSI_RED_COL">>> Invalid Standart Choice"ANSI_COL_RESET"\n");
        printf("Press \"Enter\" to exit: ");
        clean_output();
        return 1;
    }

    if (!get_message(message, sizeof(message))) {
        printf("Press \"Enter\" to exit: ");
        clean_output();
        return 1;
    }

    encode_message(message, standart);

    printf("Press \"Enter\" to exit: ");
    clean_output();

    return 0;
}
