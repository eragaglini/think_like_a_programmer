#include <iostream>

int getInt()
{
    int num = 0;
    char digit = std::cin.get();
    while (digit != 10)
    {
        num = (num * 10) + (digit - '0');
        digit = std::cin.get();
    }
    return num;
}

void printWhitespaces(int whitespaces)
{
    for (size_t i = 0; i < whitespaces; i++)
    {
        /* code */
        std::cout << " ";
    }
}

void printHashes(int hashNum)
{
    for (size_t i = 0; i < hashNum; i++)
    {
        /* code */
        std::cout << "#";
    }
}

void printFirstShapeRow(int num, int row)
{
    printWhitespaces((num - row) / 2);
    printHashes(row);
    printWhitespaces((num - row) / 2);
    std::cout << "\n";
}

void printFirstShape(int num)
{

    for (int row = 0; row < num; row++)
    {
        /* code */
        if (row % 2 == 0)
        {
            /* code */
            printFirstShapeRow(num, row);
        }
    }
    for (int row = num; row > 0; row--)
    {
        /* code */
        if (row % 2 == 0)
        {
            /* code */
            printFirstShapeRow(num, row);
        }
    }
}

void printSecondShapeRow(int hashNum, int whitespaces, int row)
{
    printWhitespaces(row);
    printHashes(hashNum);
    printWhitespaces(whitespaces);
    printHashes(hashNum);
    printWhitespaces(row);
    std::cout << "\n";
}

void printSecondShape(int num)
{
    int size = (num * 2) + ((num - 1) * 2);
    for (int row = 0; row < num; row++)
    {
        int hashNum = row + 1;
        int whitespaces = size - ((hashNum + row) * 2);
        printSecondShapeRow(hashNum, whitespaces, row);
    }
    for (int row = num; row > 0; row--)
    {
        /* code */
        int hashNum = row;
        int whitespaces = size - (((hashNum * 2) - 1) * 2);
        printSecondShapeRow(hashNum, whitespaces, (hashNum - 1));
    }
}

int main()
{
    int num = 0;
    do
    {
        /* code */
        std::cout << "Enter an even number: ";
        num = getInt();

    } while (num % 2 != 0);

    printFirstShape(num);
    printSecondShape(num);

    std::cout << "\n";
    return 0;
}
