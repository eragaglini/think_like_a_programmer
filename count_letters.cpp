// C++ Program to illustrate how to read a file character by
// character
#include <fstream>
#include <iostream>
using namespace std;

int main()
{
    // Open the file
    ifstream file("sample_text.txt");

    // Check if the file was opened successfully
    if (!file)
    {
        cout << "Unable to open file";
        return 1;
    }

    // Read the file character by character
    char ch;
    int max = 0;
    int length;
    while (file.get(ch))
    {
        length = 1;
        while (file.get(ch) && ch != ' ' && ch != '\n')
        {
            length++;
        }
        if (length > max)
        {
            max = length;
        }
    }

    // Close the file
    file.close();

    cout << "The longest word is " << max << " characters long." << endl;

    return 0;
}
