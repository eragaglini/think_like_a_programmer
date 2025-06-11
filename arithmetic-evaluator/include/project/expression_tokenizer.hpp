#include <string>
#include <vector>

using namespace std;

struct token
{
    char c;
    float f;
    bool number;

    token() : c(0), number(false) {};
    token(bool number, float f, char c) : c(c), f(f), number(number) {}
};

vector<token> tokenize_expression(const string& input);

std::string token_to_string(const token& t);

string token_vector_to_string(const vector<token>& tokens);

