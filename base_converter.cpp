// Your First C++ Program

#include <iostream>

int getInt()
{
    int num = 0;
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
        return false;
    }
    return num;
}

int getBase(bool from = true)
{

    int base = 0;
    do
    {
        /* code */
        std::cout << (from ? "From " : "To ") << "base (2-16): ";
        base = getInt();
        if (base < 2 || base > 16)
        {
            /* code */
            std::cout << "Invalid input.\n";
        }
    } while (base < 2 || base > 16);
    return base;
}

int convertToDecimal(int base)
{
    int decimal = 0;
    char character = std::cin.get();
    while (character != 10)
    {
        int digit;
        if (character >= '0' && character <= '9')
        {
            digit = character - '0';
        }
        else if (character >= 'A' && character <= 'Z')
        {
            digit = character - 'A' + 10;
        }
        else if (character >= 'a' && character <= 'z')
        {
            digit = character - 'a' + 10;
        }
        else
        {
            // error: invalid character
            return -1;
        }

        decimal = (decimal * base) + digit;
        character = std::cin.get();
    }
    return decimal;
}

char printDecimal(int decimal)
{
    if (decimal < 10)
    {
        return '0' + decimal;
    }
    else
    {
        return 'A' + decimal - 10;
    }
}

void convertToBase(int decimal, int base)
{
    if (decimal < base)
    {
        /* code */
        std::cout << printDecimal(decimal);
        return;
    }
    convertToBase(decimal / base, base);
    std::cout << printDecimal(decimal % base);
}

int main()
{
    std::cout << "Welcome to the base converter!\n";
    std::cout << "Please enter the base of the number you want to convert and the base you want to convert it to.\n";

    int from_base = getBase();
    int to_base = getBase(false);
    int decimal = 0;
    std::cout << "Enter a number: ";
    decimal = convertToDecimal(from_base);

    // std::cout << "The number in base 10 is: " << decimal << "\n";

    std::cout << "The number in base " << to_base << " is: ";
    convertToBase(decimal, to_base);
    std::cout << "\n";

    return 0;
}
