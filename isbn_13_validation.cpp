// Your First C++ Program

#include <iostream>
#include <cmath>
enum modeType
{
    VALIDATION,
    GENERATE_CHECK_DIGIT,
    INVALID_INPUT
};

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

int getCheckDigit(int sum)
{
    int remainder = sum % 10;
    int checkDigit = remainder == 0 ? 0 : 10 - remainder;
    return checkDigit;
}

int main()
{
    modeType mode = getInputMode();

    int position = 0;
    int sum = 0;
    int multiplier = 1;
    char digit;
    int lastDigit = 0;
    std::cout << "Enter a number: ";
    digit = std::cin.get();
    while (digit != 10)
    {
        if (!isdigit(digit))
        {
            std::cout << "Invalid input.\n";
            return 0;
        }
        if (position < 12)
            sum += (digit - '0') * multiplier;
        digit = std::cin.get();
        position++;

        if (position == 12)
        {
            /* code */
            lastDigit = digit - '0';
        }

        multiplier = multiplier == 1 ? 3 : 1;
    }

    if (mode == GENERATE_CHECK_DIGIT && position != 12)
    {
        std::cout << "Invalid input.\n";
        return 0;
    }

    else if (mode == GENERATE_CHECK_DIGIT)
    {
        int checkDigit = getCheckDigit(sum);
        std::cout << "Check digit is " << checkDigit << ".\n";
        return 0;
    }

    else if (mode == VALIDATION && position != 13)
    {
        std::cout << "Invalid input.\n";
        return 0;
    }

    if (lastDigit == getCheckDigit(sum))
    {
        {
            /* code */
            std::cout << "Valid.\n";
        }
    }
    else
    {
        std::cout << "Invalid.\n";
    }

    return 0;
}
