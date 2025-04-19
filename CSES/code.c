#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define BUFFER_SIZE 100

bool parsed_int(char *string, int *integer);

int main(void) {
    char buffer[BUFFER_SIZE];
    int integer = 0;
    bool parsed_correct = true;

    do {
        printf("Enter a number: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        // Remove newline character if present
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        parsed_correct = parsed_int(buffer, &integer);
        if (!parsed_correct) {
            printf("Enter a valid number.\n\n");
        }
    } while (!parsed_correct);

    printf("You entered: %d\n", integer);
    return 0;
}

bool parsed_int(char *string, int *integer) {
    int i = 0;

    // Skip leading whitespace
    while (isspace(string[i])) i++;

    int length = strlen(string);
    if (i == length) return false;

    char integer_buffer[BUFFER_SIZE];
    int integer_chars = 0;

    // Optional negative sign
    if (string[i] == '-') {
        integer_buffer[integer_chars++] = string[i++];
        if (!isdigit(string[i])) return false; // Must be followed by digit
    }

    // Check digits
    while (i < length && isdigit(string[i])) {
        integer_buffer[integer_chars++] = string[i++];
    }

    integer_buffer[integer_chars] = '\0';

    // Skip trailing whitespace
    while (isspace(string[i])) i++;

    // If anything else remains, it's invalid
    if (string[i] != '\0') return false;

    *integer = atoi(integer_buffer);
    return true;
}