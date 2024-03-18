#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 1000

typedef struct {
    char encrypted_text[MAX_LENGTH];
    int encryption_key[MAX_LENGTH];
} CharCryptor;

// Function to generate a random encryption key
void generate_encryption_key(CharCryptor *cipher, int length) {
    for (int i = 0; i < length; i++) {
        cipher->encryption_key[i] = rand() % 26; // Generates a random number between 0 and 25
    }
}

// Function to encrypt the text
void encrypt(CharCryptor *cipher) {
    int length = strlen(cipher->encrypted_text);
    for (int i = 0; i < length; i++) {
        if (isdigit(cipher->encrypted_text[i])) {
            // Encrypt digits by shifting by 1
            cipher->encrypted_text[i] = ((cipher->encrypted_text[i] - '0' + 1) % 10) + '0';
        }
        else if (isalpha(cipher->encrypted_text[i])) {
            if (islower(cipher->encrypted_text[i])) {
                // Encrypt lowercase letters using encryption key
                cipher->encrypted_text[i] = ((cipher->encrypted_text[i] - 'a' + cipher->encryption_key[i]) % 26) + 'a';
            }
            else if (isupper(cipher->encrypted_text[i])) {
                // Encrypt uppercase letters using encryption key
                cipher->encrypted_text[i] = ((cipher->encrypted_text[i] - 'A' + cipher->encryption_key[i]) % 26) + 'A';
            }
        }
    }
}

// Function to decrypt the text
void decrypt(CharCryptor *cipher) {
    int length = strlen(cipher->encrypted_text);
    for (int i = 0; i < length; i++) {
        if (isdigit(cipher->encrypted_text[i])) {
            // Decrypt digits by shifting back by 1
            cipher->encrypted_text[i] = ((cipher->encrypted_text[i] - '0' - 1 + 10) % 10) + '0';
        }
        else if (isalpha(cipher->encrypted_text[i])) {
            if (islower(cipher->encrypted_text[i])) {
                // Decrypt lowercase letters using encryption key
                cipher->encrypted_text[i] = ((cipher->encrypted_text[i] - 'a' - cipher->encryption_key[i] + 26) % 26) + 'a';
            }
            else if (isupper(cipher->encrypted_text[i])) {
                // Decrypt uppercase letters using encryption key
                cipher->encrypted_text[i] = ((cipher->encrypted_text[i] - 'A' - cipher->encryption_key[i] + 26) % 26) + 'A';
            }
        }
    }
}

int main() {
    char input_text[MAX_LENGTH];
    printf("Enter your message: ");
    fgets(input_text, MAX_LENGTH, stdin);
    input_text[strcspn(input_text, "\n")] = '\0';

    if (strlen(input_text) == 0) {
        printf("Please enter a message.\n");
        return 1;
    }

    CharCryptor cipher;
    strcpy(cipher.encrypted_text, input_text);
    generate_encryption_key(&cipher, strlen(input_text)); // Generate encryption key based on input text length

    encrypt(&cipher); // Encrypt the input text
    printf("Encrypted text: %s\n", cipher.encrypted_text);

    char response[10];
    printf("Do you want to decrypt the text? (yes/no): ");
    fgets(response, 10, stdin);
    response[strcspn(response, "\n")] = '\0';

    if (strcmp(response, "yes") == 0) {
        decrypt(&cipher); // Decrypt the encrypted text
        printf("Decrypted text: %s\n", cipher.encrypted_text);
    } else {
        printf("Exiting the program.\n");
    }

    return 0;
}
