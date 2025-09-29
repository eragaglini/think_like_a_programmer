// Your First C++ Program

#include <iostream>
enum modeType
{
    UPPERCASE,
    LOWERCASE,
    PUNCTUATION
};

int main()
{
    char input;

    std::cout << "Enter a message: ";
    input = std::cin.get();
    modeType mode = UPPERCASE;
    // while (input != 10) {
    while (true)
    {
        int n = 0;
        while ((input != 44) && (input != 10))
        {
            /* code */
            n = ((n * 10) + (input - '0'));
            input = std::cin.get();
        }
        int remainder = mode == PUNCTUATION ? n % 9 : n % 27;
        // convert from number to character
        // according to the mode
        switch (mode)
        {
        case UPPERCASE:
            /* code */
            if (remainder == 0)
                mode = LOWERCASE;
            else
                std::cout << char(remainder + 'A' - 1);
            break;
        case LOWERCASE:
            /* code */
            if (remainder == 0)
                mode = PUNCTUATION;
            else
                std::cout << char(remainder + 'a' - 1);
            break;
        case PUNCTUATION:
            /* code */
            if (remainder == 0)
            {
                mode = UPPERCASE;
            }
            else
            {
                switch (remainder)
                {
                case 1:
                    /* code */
                    std::cout << '!';
                    break;

                case 2:
                    /* code */
                    std::cout << '?';
                    break;

                case 3:
                    /* code */
                    std::cout << ',';
                    break;

                case 4:
                    /* code */
                    std::cout << '.';
                    break;

                case 5:
                    /* code */
                    std::cout << ' ';
                    break;

                case 6:
                    /* code */
                    std::cout << ';';
                    break;

                case 7:
                    /* code */
                    std::cout << '"';
                    break;

                case 8:
                    /* code */
                    std::cout << '\'';
                    break;
                }
            }
        }
        if (input == 10)
            break;
        input = std::cin.get();
    }
    std::cout << "\n";
    return 0;
}
