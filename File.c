#include <stdio.h>
#include <stdlib.h> // Include for free and malloc
#include <string.h>
#include <ctype.h> // Include for isupper and islower

// Function prototypes
void readFile(char *filename, char *buffer);
char* encryptText(const char *text, int shift);
void writeFile(char *encryptedText, const char *outputFilename);

int main() {
    char originalText[1000]; // Buffer to hold the original text
    char *encryptedText; // Pointer to dynamically allocate memory for encrypted text

    // Prompt user for the name of the file to be encrypted
    printf("Enter the name of the file to be encrypted: ");
    // Use fgets to read the entire line of input, including spaces
    fgets(originalText, sizeof(originalText), stdin);
    // Remove the trailing newline character from the input
    originalText[strcspn(originalText, "\n")] = 0;

    // Read the content of the specified file into the buffer
    readFile(originalText, originalText);

    // Encrypt the text using a Caesar cipher with a shift of 3
    encryptedText = encryptText(originalText, 3);

    // Prompt user for the name of the output file
    printf("Enter the name of the output file: ");
    // Use fgets to read the entire line of input, including spaces
    fgets(encryptedText, sizeof(encryptedText), stdin);
    // Remove the trailing newline character from the input
    encryptedText[strcspn(encryptedText, "\n")] = 0;

    // Write the encrypted text to the specified output file
    writeFile(encryptedText, encryptedText);

    // Free the dynamically allocated memory for the encrypted text
    free(encryptedText);

    return 0;
}

// Reads the content of the specified file into the provided buffer
void readFile(char *filename, char *buffer) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return;
    }

    // Read one line from the file into the buffer
    fgets(buffer, sizeof(buffer), file);
    fclose(file);
}

// Encrypts the given text using a Caesar cipher with the specified shift
char* encryptText(const char *text, int shift) {
    int length = strlen(text);
    char *encryptedText = malloc((length + 1) * sizeof(char)); // Allocate memory for encrypted text
    if (encryptedText == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    for (int i = 0; i < length; ++i) {
        // Encrypt uppercase letters
        if (isupper(text[i])) {
            encryptedText[i] = 'A' + ((text[i] - 'A' + shift) % 26);
        }
        // Encrypt lowercase letters
        else if (islower(text[i])) {
            encryptedText[i] = 'a' + ((text[i] - 'a' + shift) % 26);
        }
        // Leave non-alphabetic characters unchanged
        else {
            encryptedText[i] = text[i];
        }
    }

    // Null-terminate the encrypted text string
    encryptedText[length] = '\0';
    return encryptedText;
}

// Writes the encrypted text to the specified output file
void writeFile(char *encryptedText, const char *outputFilename) {
    FILE *file = fopen(outputFilename, "w");
    if (file == NULL) {
        printf("Could not open file %s for writing\n", outputFilename);
        return;
    }

    // Write the encrypted text to the file
    fputs(encryptedText, file);
    fclose(file);
}
