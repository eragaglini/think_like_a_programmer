#include "project/hangman.hpp"
#include <boost/range/adaptors.hpp>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <unistd.h>
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

enum Mode
{
    PLAYER1,
    PLAYER2,
};

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

bool is_letters(string input)
{
    for (int i = 0; i < input.size(); i++)
    {
        int uppercaseChar = toupper(
            input[i]); // Convert character to upper case version of character
        if (uppercaseChar < 'A' ||
            uppercaseChar > 'Z') // If character is not A-Z
        {
            return false;
        }
    }
    // At this point, we have gone through every character and checked it.
    return true; // Return true since every character had to be A-Z
}

string get_letter_from_input()
{
    string character;
    cout << "\nPlease input a letter: ";
    cin >> character;
    while (!cin.good() || !is_letters(character))
    {
        cout << "You have entered an invalid input, please input a letter: ";
        cin.ignore(1024, '\n');
        cin >> character;
    }
    return character;
}

void display_winning_message(string word)
{
    cout << "Right!!! You win!" << endl;
    cout << "The word was: " << word << endl;
}

void to_lower_string(string& data)
{

    std::transform(data.begin(), data.end(), data.begin(),
                   [](unsigned char c) { return std::tolower(c); });
}

void play_as_player1(vector<string>& wordVector, int guesses, string pattern)
{
    vector<string> guessed_letters;
    while (guesses > 0)
    {
        string ch = get_letter_from_input();
        to_lower_string(ch);
        if ((ch.length() > 1) && (wordVector.size() == 1) &&
            (ch == wordVector[0]))
        {
            /* code */
            display_winning_message(wordVector[0]);
            return;
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
                display_winning_message(wordVector[0]);
                return;
            }
        }
        cout << pattern << endl;
        if (!is_in_vector(guessed_letters, ch))
        {
            guessed_letters.push_back(ch);
            guesses--;
            cout << "\nYou have: " << guesses << " guesses left!" << endl;
        }
        else
        {
            cout << "\nYou already tried that letter!" << endl;
        }
    }
    cout << "Wrong answer!" << endl;
    cout << "You lost!" << endl;
}

std::vector<std::string> get_alphabet_vector()
{
    std::vector<std::string> alphabet_vector;

    for (char c = 'a'; c <= 'z'; ++c)
    {
        alphabet_vector.push_back(std::string(1, c));
    }
    return alphabet_vector;
}

void play_as_player2(vector<string>& wordVector, int guesses, string pattern)
{
    cout << "Playing as player2..." << endl;
    cout << "Available words for you to choose: " << endl;
    for (size_t i = 0; i < wordVector.size(); i++)
    {
        cout << wordVector[i] << endl;
    }
    string guess;
    // vector<string> remaining_letters = get_alphabet_vector();
    vector<string> guessed_letters;
    while (guesses > 0)
    {
        cout << "Computer thinking..." << endl;
        sleep(3); // sleeps for 3 second
        string best_guess =
            get_best_guess(wordVector, guessed_letters, pattern);
        cout << "How about letter " << best_guess << "? (y/n)" << endl;

        do
        {
            guess = get_letter_from_input();
        } while ((guess != "n") && (guess != "y"));
        if (guess == "n")
        {
            /* code */
            guesses--;
            cout << "Computer has: " << guesses << " guesses left!" << endl;
        }
        else
        {
            cout << "Where does the letter appear?" << endl;
            cout << "So far the word is: " << pattern << endl;
            cin >> pattern; // get user input from the keyboard
        }
        guessed_letters.push_back(best_guess);
        wordVector = update_word_vector(wordVector, pattern, guessed_letters);
        if (pattern.find('_') == std::string::npos)
        {
            cout << "Computer Won!" << endl;
            return;
        }
    }
    cout << "Wrong answer!" << endl;
    cout << "You lost!" << endl;
}

void play_game(Mode mode)
{

    cout << "How many guesses do you need?" << endl;
    int guesses = get_number_from_input();
    while (guesses < 1)
    {
        cout << "Invalid input" << endl;
        cout << "How many guesses do you need?" << endl;
        guesses = get_number_from_input();
    }

    cout << "How long does the word have to be? (3-6 letters)" << endl;

    int length = get_number_from_input();
    while ((length < 3) || (length > 6))
    {
        length = get_number_from_input();
    }

    std::ifstream ifs(get_words_file_path()); // note no mode needed
    if (!ifs.is_open())
    {
        cout << " Failed to open" << endl;
        return;
    }

    vector<string> wordVector = get_word_vector_from_file(ifs, length);

    // cout << "available words: " << endl;
    // for (size_t i = 0; i < wordVector.size(); i++)
    // {
    //     cout << wordVector[i] << endl;
    // }

    std::string pattern(length, '_');

    if (mode == PLAYER1)
    {
        play_as_player1(wordVector, guesses, pattern);
    }
    else
    {
        play_as_player2(wordVector, guesses, pattern);
    }
}

Mode get_mode()
{
    cout << "Do you want to guess the word (1) or do the computer do the "
            "guessing (2)? "
         << endl;
    int mode = get_number_from_input();
    while ((mode != 1) && (mode != 2))
    {
        /* code */
        mode = get_number_from_input();
    }
    switch (mode)
    {
        case 1:
            /* code */
            return PLAYER1;

        default:
            return PLAYER2;
    }
}

int main()
{
    cout << "Welcome to Hangman (with a twist)!" << endl;

    string playing = "y";

    while (playing == "y")
    {
        Mode mode = get_mode();

        play_game(mode);

        cout << "Do you want to play another game? (y/n)" << endl;

        do
        {
            playing = get_letter_from_input();
        } while ((playing != "n") && (playing != "y"));
    }
    return 0;
}
