import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Random;

public class CharCryptor {
    private StringBuilder encryptedText;
    private int[] encryptionKey;

    public CharCryptor(String text) {
        this.encryptedText = new StringBuilder(text);
        this.encryptionKey = generateEncryptionKey(text.length());
    }

    // Generate a random encryption key
    private int[] generateEncryptionKey(int length) {
        int[] key = new int[length];
        Random random = new Random();
        for (int i = 0; i < length; i++) {
            key[i] = random.nextInt(26);  // Limiting the shift to 26 (number of letters in the alphabet)
        }
        return key;
    }

    // Encrypt the text
    public void encrypt() {
        for (int i = 0; i < encryptionKey.length; i++) {
            encryptedText.setCharAt(i, shiftCharForward(encryptedText.charAt(i), encryptionKey[i]));
        }
        encryptIntegers();
    }

    // Decrypt the text
    public void decrypt() {
        decryptIntegers();
        for (int i = 0; i < encryptionKey.length; i++) {
            encryptedText.setCharAt(i, shiftCharBackward(encryptedText.charAt(i), encryptionKey[i]));
        }
    }

    // Shift characters forward in the alphabet and handle integer encryption
    private char shiftCharForward(char c, int shift) {
        if (Character.isLowerCase(c)) {
            return (char) ((c - 'a' + shift) % 26 + 'a');
        } else if (Character.isUpperCase(c)) {
            return (char) ((c - 'A' + shift) % 26 + 'A');
        } else {
            return c; // Leave non-alphabetic characters unchanged
        }
    }

    // Shift characters backward in the alphabet and handle integer decryption
    private char shiftCharBackward(char c, int shift) {
        if (Character.isLowerCase(c)) {
            return (char) ((c - 'a' - shift + 26) % 26 + 'a');
        } else if (Character.isUpperCase(c)) {
            return (char) ((c - 'A' - shift + 26) % 26 + 'A');
        } else {
            return c; // Leave non-alphabetic characters unchanged
        }
    }

    // Encrypt integers within the text
    private void encryptIntegers() {
        StringBuilder encryptedString = new StringBuilder();

        for (char c : encryptedText.toString().toCharArray()) {
            if (Character.isDigit(c)) {
                // Encrypt digit using a shifting operation (for example, shifting by 1)
                char encryptedDigit = (char) (((c - '0') + 1) % 10 + '0');
                encryptedString.append(encryptedDigit);
            } else {
                encryptedString.append(c);
            }
        }
        encryptedText = encryptedString;
    }

    // Decrypt integers within the text
    private void decryptIntegers() {
        StringBuilder decryptedString = new StringBuilder();

        for (char c : encryptedText.toString().toCharArray()) {
            if (Character.isDigit(c)) {
                // Decrypt digit using a shifting operation (shifting back by 1)
                char decryptedDigit = (char) (((c - '0') - 1 + 10) % 10 + '0');
                decryptedString.append(decryptedDigit);
            } else {
                decryptedString.append(c);
            }
        }
        encryptedText = decryptedString;
    }

    // Override toString() to return the encrypted text
    @Override
    public String toString() {
        return encryptedText.toString();
    }

    public static void main(String[] args) {
        System.out.println("Enter your message:");
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        try {
            String inputText = reader.readLine();
            if (inputText.isEmpty()) {
                System.out.println("Please enter a message.");
            } else {
                CharCryptor cipher = new CharCryptor(inputText);
                cipher.encrypt();
                System.out.println("Encrypted text: " + cipher);
                System.out.println("Do you want to decrypt the text? (yes/no)");
                String response = reader.readLine();
                if ("yes".equalsIgnoreCase(response)) {
                    cipher.decrypt();
                    System.out.println("Decrypted text: " + cipher);
                } else {
                    System.out.println("Exiting the program.");
                }
            }
        } catch (IOException e) {
            System.out.println("An error occurred while reading input: " + e.getMessage());
        }
    }
}