#include <iostream>
#include <string.h>
#include <algorithm>
#include <ctime>

using namespace std;

const char alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
// const char cipherAlphabet[] = {'J', 'A', 'Z', 'E', 'K', 'R', 'T', 'N', 'D', 'F', 'G', 'Y', 'C', 'Q', 'V', 'B', 'H', 'M', 'W', 'X', 'I', 'P', 'L', 'O', 'S', 'U'};
const int ALPHABET_LENGHT = 26;

int getposition(const char *array, size_t size, char c)
{
    const char *end = array + size;
    const char *match = std::find(array, end, c);
    return (end == match) ? -1 : (match - array);
}

void getCipherText(const char charArray1[], char result[], int textLength, const char from[], const char to[])
{
    for (size_t i = 0; i < textLength; i++)
    {
        /* code */
        int index = getposition(from, 26, charArray1[i]);
        if (index != -1)
        {
            result[i] = to[index];
        }
        else
        {
            result[i] = charArray1[i];
        }
    }
}

int main()
{

    // set seed to time(0)
    srand(time(0));

    // creatin a cipher alphabet by copying and shuffling the alphabet
    char cipherAlphabet[ALPHABET_LENGHT];
    strncpy(cipherAlphabet, alphabet, 26);
    random_shuffle(&cipherAlphabet[0], &cipherAlphabet[25]);
    cout << cipherAlphabet << endl;

    char plainText[] = "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG, PACKING MY BOX WITH FIVE DOZEN LIQUOR JUGS.";
    int textLength = sizeof(plainText) / sizeof(char);
    char cipherText[textLength];
    getCipherText(plainText, cipherText, textLength, alphabet, cipherAlphabet);

    cout << endl;
    cout << "Plain text: " << endl;
    cout << plainText << endl;
    cout << "Ciphertext: " << endl;
    cout << cipherText << endl;

    cout << "----------" << endl;

    char decodedMessage[textLength];
    getCipherText(cipherText, decodedMessage, textLength, cipherAlphabet, alphabet);

    cout << endl;
    cout << "Ciphertext: " << endl;
    cout << cipherText << endl;
    cout << "Decoded Message: " << endl;
    cout << decodedMessage << endl;
    return 0;
}
