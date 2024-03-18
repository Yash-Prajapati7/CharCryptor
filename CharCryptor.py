import random

class CharCryptor:
    def __init__(self, text):
        self.encrypted_text = list(text)  # Convert the input text into a list of characters
        self.encryption_key = self.generate_encryption_key(len(text))  # Generate encryption key based on the length of input text

    def generate_encryption_key(self, length):
        key = [random.randint(0, 25) for _ in range(length)]  # Generate a list of random integers as encryption key
        return key

    def encrypt(self):
        self.encrypt_integers()  # Encrypt any digits present in the text
        for i in range(len(self.encryption_key)):
            # Shift each character forward in the alphabet based on the encryption key
            self.encrypted_text[i] = self.shift_char_forward(self.encrypted_text[i], self.encryption_key[i])

    def decrypt(self):
        for i in range(len(self.encryption_key)):
            # Shift each character backward in the alphabet based on the encryption key to decrypt
            self.encrypted_text[i] = self.shift_char_backward(self.encrypted_text[i], self.encryption_key[i])
        self.decrypt_integers()  # Decrypt any encrypted digits present in the text

    def shift_char_forward(self, c, shift):
        if c.islower():
            return chr(((ord(c) - ord('a') + shift) % 26) + ord('a'))  # Shift lowercase characters
        elif c.isupper():
            return chr(((ord(c) - ord('A') + shift) % 26) + ord('A'))  # Shift uppercase characters
        else:
            return c  # Return unchanged for non-alphabetic characters

    def shift_char_backward(self, c, shift):
        if c.islower():
            return chr(((ord(c) - ord('a') - shift + 26) % 26) + ord('a'))  # Shift backward for lowercase characters
        elif c.isupper():
            return chr(((ord(c) - ord('A') - shift + 26) % 26) + ord('A'))  # Shift backward for uppercase characters
        else:
            return c  # Return unchanged for non-alphabetic characters

    def encrypt_integers(self):
        for i in range(len(self.encrypted_text)):
            if self.encrypted_text[i].isdigit():
                encrypted_digit = str((int(self.encrypted_text[i]) + 1) % 10)  # Encrypt digit by shifting
                self.encrypted_text[i] = encrypted_digit

    def decrypt_integers(self):
        for i in range(len(self.encrypted_text)):
            if self.encrypted_text[i].isdigit():
                decrypted_digit = str((int(self.encrypted_text[i]) - 1 + 10) % 10)  # Decrypt digit by shifting back
                self.encrypted_text[i] = decrypted_digit

    def __str__(self):
        return ''.join(self.encrypted_text)  # Convert the list of characters back to a string

if __name__ == "__main__":
    input_text = input("Enter your message: ")
    if not input_text:
        print("Please enter a message.")
    else:
        cipher = CharCryptor(input_text)
        cipher.encrypt()  # Encrypt the input text
        print("Encrypted text:", cipher)
        response = input("Do you want to decrypt the text? (yes/no): ")
        if response.lower() == "yes":
            cipher.decrypt()  # Decrypt the encrypted text
            print("Decrypted text:", cipher)
        else:
            print("Exiting the program.")
