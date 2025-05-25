#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include "project/hangman.hpp"

using namespace std;

/*
Hangman game (with a twist).

         _________
         |       |
         O       |
        \|/      |
         |       |
        / \      |
                 |
                ---

*/

int get_number_from_input()
{
  int x;
    std::cin >> x;
    while(std::cin.fail()) {
        std::cout << "Error" << std::endl;
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cin >> x;
    }
    return x;
}

int main()
{
    std::ifstream ifs(getWordsFilePath()); // note no mode needed
    if (!ifs.is_open())
    {
        cout << " Failed to open" << endl;
        return 1;
    }
    else
    {
        cout << "Opened OK" << endl;
    }
    string secret;
    // Get a different random number each time the program runs
    srand(time(0));
    // Generate a random number between 0 and 100
    int random_num = rand() % 1001;
    secret = get_word_from_file(ifs, random_num);
    string result = string(secret.length(), '_');

    cout << "Welcome to Hangman!" << endl;

    cout << "How many guesses do you want?" << endl;
    int max_guesses = get_number_from_input();
    int guesses = 0;
    cout << "Maximum " << max_guesses << " mistakes are allowed\n\n";
    cout << " ----------- \n";

    while (guesses < max_guesses)
    {
        cout << "\nGuesses: " << guesses << "\n\n";
        char letter;
        cin >> letter;
        auto pos = secret.find(letter);
        cout << "\n";
        if (pos == string::npos)
        {
            guesses++;
        }
        else
        {
            for (size_t i = 0; i < result.size(); i++)
            {
                if (secret[i] == letter)
                {
                    result[i] = letter;
                }
            }
        }

        cout << "\n";
        cout << result << endl;

        if (result.find('_') == string::npos)
        {
            cout << "You won!" << endl;
            return 0;
        }
    }

    cout << "You lost!" << endl;
    cout << "The solution was: " << secret << endl;

    return 0;
}
