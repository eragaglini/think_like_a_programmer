// Your First C++ Program

#include <iostream>
#include <cmath>
enum modeType
{
    VALIDATION,
    GENERATE_CHECK_DIGIT,
    INVALID_INPUT
};

int countDigitsLong(unsigned long long n)
{
    if (n == 0)
        return 1;
    return std::floor(std::log10(n)) + 1;
}

unsigned long long getInt(int length)
{
    unsigned long long num = 0;
    char digit = std::cin.get();
    bool invalid = false;
    while (digit != 10)
    {
        /* code */
        if (!isdigit(digit))
        {
            invalid = true;
        }
        num = (num * 10) + (digit - '0');
        digit = std::cin.get();
    }
    if (invalid)
    {
        return 1;
    }
    return countDigitsLong(num) == length ? num : 1;
}

modeType getMode()
{
    char character = std::cin.get();
    int length = character == 10 ? 0 : 1;
    modeType mode = character == 'c' && length == 1 ? VALIDATION : character == 'g' && length == 1 ? GENERATE_CHECK_DIGIT
                                                                                                   : INVALID_INPUT;
    character = std::cin.get();
    while (character != 10)
    {
        /* code */
        character = std::cin.get();
        length++;
    }
    return length == 1 ? mode : INVALID_INPUT;
}

unsigned long long getInputNumber(int length)
{
    unsigned long long num = 0;
    do
    {
        /* code */
        std::cout << "Enter a valid number: ";
        num = getInt(length);
        if (num == 1)
        {
            /* code */
            std::cout << "Invalid input.\n";
        }
    } while (num == 1);
    return num;
}

modeType getInputMode()
{

    modeType mode = VALIDATION;
    do
    {
        /* code */
        std::cout << "Do you want to check an ISBN-13 or generate a check digit? (c, g) ";
        mode = getMode();
        if (mode == INVALID_INPUT)
        {
            /* code */
            std::cout << "Invalid input.\n";
        }
    } while (mode == INVALID_INPUT);
    return mode;
}

int getFirstDigitString(std::string s)
{
    return s[0] - '0'; // Access the first character and convert back to integer
}

int sumOfDigitsMSDRecursive(std::string s, int multiplier = 1)
{
    if (s.size() == 1)
        return getFirstDigitString(s) * multiplier;
    return getFirstDigitString(s) * multiplier + sumOfDigitsMSDRecursive(s.substr(1), multiplier == 1 ? 3 : 1);
}

int generateCheckDigit(unsigned long long num)
/*
    ISBN-13 checksum
    An ISBN-13 check digit ranges from 0 to 9, and is computed using similar steps:
    Multiply each of the first 12 digits by 1 or 3, alternating as you move from left to right, and sum the results.
    Divide the sum by 10.
    Subtract the remainder (not the quotient) from 10.
    If the result is 10, use the number 0.
*/
{
    int sum = sumOfDigitsMSDRecursive(std::to_string(num));
    int checkDigit = (sum % 10 == 0) ? 0 : 10 - (sum % 10);
    if (checkDigit == 10)
    {
        return 0;
    }
    else
    {
        return checkDigit;
    }
}

void checkNumber(unsigned long long num)
{
    if (generateCheckDigit(std::stoull(std::to_string(num).substr(0, 12))) != num % 10)
    {
        std::cout << "The ISBN-13 number is not valid.\n";
        return;
    }
    std::cout << "The ISBN-13 number is valid.\n";
}

int main()
{
    modeType mode = getInputMode();
    int length = mode == VALIDATION ? 13 : 12;
    unsigned long long num = getInputNumber(length);

    if (mode == GENERATE_CHECK_DIGIT)
        std::cout << "Check digit: " << num << " is: " << generateCheckDigit(num) << "\n";
    else if (mode == VALIDATION)
        checkNumber(num);

    return 0;
}
