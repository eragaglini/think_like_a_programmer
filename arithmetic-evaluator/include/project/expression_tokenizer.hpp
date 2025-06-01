#include <any>
#include <string>
#include <vector>

using namespace std;

bool is_operator(char ch);

struct token
{
    char c;
    float f;
    bool number;

    token() : number(false), c(0) {};
};

vector<token> tokenize_expression(const string& input);
