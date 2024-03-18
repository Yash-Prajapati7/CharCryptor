#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class CharCryptor {
private:
    string encrypted_text;
    vector<int> encryption_key; // Using vector for encryption key

public:
    CharCryptor(string text) {
        encrypted_text = text;
        generate_encryption_key(text.length()); // Generate encryption key based on the length of the input text
    }

    // Function to generate a random encryption key and store it in a vector
    void generate_encryption_key(int length) {
        srand(time(0));
        for (int i = 0; i < length; i++) {
            encryption_key.push_back(rand() % 26); // Add a random number to the encryption key vector
        }
    }

    // Function to encrypt the text
    void encrypt() {
        for (size_t i = 0; i < encrypted_text.length(); i++) {
            if (isdigit(encrypted_text[i])) {
                encrypted_text[i] = ((encrypted_text[i] - '0' + 1) % 10) + '0'; // Encrypt digits
            }
            else if (isalpha(encrypted_text[i])) {
                if (islower(encrypted_text[i])) {
                    encrypted_text[i] = ((encrypted_text[i] - 'a' + encryption_key[i]) % 26) + 'a'; // Encrypt lowercase letters
                }
                else if (isupper(encrypted_text[i])) {
                    encrypted_text[i] = ((encrypted_text[i] - 'A' + encryption_key[i]) % 26) + 'A'; // Encrypt uppercase letters
                }
            }
        }
    }

    // Function to decrypt the text
    void decrypt() {
        for (size_t i = 0; i < encrypted_text.length(); i++) {
            if (isdigit(encrypted_text[i])) {
                encrypted_text[i] = ((encrypted_text[i] - '0' - 1 + 10) % 10) + '0'; // Decrypt digits
            }
            else if (isalpha(encrypted_text[i])) {
                if (islower(encrypted_text[i])) {
                    encrypted_text[i] = ((encrypted_text[i] - 'a' - encryption_key[i] + 26) % 26) + 'a'; // Decrypt lowercase letters
                }
                else if (isupper(encrypted_text[i])) {
                    encrypted_text[i] = ((encrypted_text[i] - 'A' - encryption_key[i] + 26) % 26) + 'A'; // Decrypt uppercase letters
                }
            }
        }
    }

    // Function to retrieve the encrypted text
    string get_encrypted_text() {
        return encrypted_text;
    }
};

int main() {
    string input_text;
    cout << "Enter your message: ";
    getline(cin, input_text);

    if (input_text.empty()) {
        cout << "Please enter a message." << endl;
        return 1;
    }

    CharCryptor cipher(input_text);
    cipher.encrypt();
    cout << "Encrypted text: " << cipher.get_encrypted_text() << endl;

    string response;
    cout << "Do you want to decrypt the text? (yes/no): ";
    getline(cin, response);

    if (response == "yes") {
        cipher.decrypt();
        cout << "Decrypted text: " << cipher.get_encrypted_text() << endl;
    } else {
        cout << "Exiting the program." << endl;
    }

    return 0;
}
