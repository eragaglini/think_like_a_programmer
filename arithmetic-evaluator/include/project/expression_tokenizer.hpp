#include <string>
#include <vector>

using namespace std;

struct token
{
    char c;
    float f;
    bool number;

    token() : number(false), c(0) {};
    token(bool number, float f, char c) : number(number), f(f), c(c) {}
};

vector<token> tokenize_expression(const string& input);

std::string token_to_string(const token& t);

string token_vector_to_string(const vector<token>& tokens);
