// Your First C++ Program

#include <iostream>
#include <cstdlib>

int doubleDigitValue(int digit)
{
    int doubledDigit = digit * 2;
    int sum;
    if (doubledDigit >= 10)
        sum = 1 + doubledDigit % 10;
    else
        sum = doubledDigit;
    return sum;
}

int main()
{
    char digit;
    int oddLengthChecksum = 0;
    int evenLengthChecksum = 0;
    int position = 1;
    std::cout << "Enter a number: ";
    digit = std::cin.get();
    while (digit != 10)
    {
        if (position % 2 == 0)
        {
            oddLengthChecksum += doubleDigitValue(digit - '0');
            evenLengthChecksum += digit - '0';
        }
        else
        {
            oddLengthChecksum += digit - '0';
            evenLengthChecksum += doubleDigitValue(digit - '0');
        }
        digit = std::cin.get();
        position++;
    }
    int checksum;
    if ((position - 1) % 2 == 0)
        checksum = evenLengthChecksum;
    else
        checksum = oddLengthChecksum;
    std::cout << "Checksum is " << checksum << ". \n";
    if (checksum % 10 == 0)
    {
        std::cout << "Checksum is divisible by 10. Valid. \n";
    }
    else
    {
        std::cout << "Checksum is not divisible by 10. Invalid. \n";
    }

    return 0;
}
