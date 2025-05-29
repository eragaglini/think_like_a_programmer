#include "project/hangman.hpp"
#include <boost/range/adaptors.hpp>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <utility>
#include <vector>

using namespace std;
using boost::adaptors::filtered;

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
    while (std::cin.fail())
    {
        std::cout << "Error" << std::endl;
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cin >> x;
    }
    return x;
}

string get_letter_from_input()
{
    string character;
    cout << "\nPlease input a letter: ";
    cin >> character;
    while (!cin.good())
    {
        cout << "You have entered an invalid input, please input a letter: ";
        cin.ignore(1024, '\n');
        cin >> character;
    }
    return character;
}

int main()
{
    cout << "Welcome to Hangman (with a twist)!" << endl;

    cout << "How many guesses do you need?" << endl;
    int guesses = get_number_from_input();

    cout << "How long does the word have to be? (3-6 letters)" << endl;

    int length = get_number_from_input();
    while ((length < 3) || (length > 6))
    {
        length = get_number_from_input();
    }

    std::ifstream ifs(get_words_file_path(length)); // note no mode needed
    if (!ifs.is_open())
    {
        cout << " Failed to open" << endl;
        return 1;
    }

    vector<string> wordVector = get_word_vector_from_file(ifs);

    // cout << "available words:: " << endl;
    // for (size_t i = 0; i < wordVector.size(); i++)
    // {
    //     cout << wordVector[i] << endl;
    // }

    std::string pattern(length, '_');

    while (guesses > 0)
    {
        string ch = get_letter_from_input();
        if ((ch.length() > 1) && (wordVector.size() == 1) &&
            (ch == wordVector[0]))
        {
            /* code */
            cout << "Right!!! You win!" << endl;
            return 0;
        }
        else if (ch.length() > 1)
        {
            /* code */
            auto itr = find(wordVector.begin(), wordVector.end(), ch);
            if (itr != wordVector.end())
                wordVector.erase(itr);

            cout << "Wrong answer!" << endl;
        }
        else
        {
            pair<string, vector<string>> best_option = get_best_option_pair(
                group_words_by_pattern(wordVector, *ch.c_str(), pattern));
            wordVector = best_option.second;
            pattern = best_option.first;

            if ((wordVector.size() == 1) && (pattern == wordVector[0]))
            {
                /* code */
                cout << "Right!!! You win!" << endl;
                return 0;
            }
        }

        // cout << "Available words remaining:" << endl;
        // for (size_t i = 0; i < wordVector.size(); i++)
        // {
        //     /* code */
        //     cout << wordVector[i] << endl;
        // }
        // cout << pattern << endl;

        guesses--;
    }

    cout << "Wrong answer!" << endl;
    cout << "You lost!" << endl;

    return 0;
}
