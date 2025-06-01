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
    bool operator==(const token& rhs) const
    {
        return this->number == rhs.number &&
               (this->number ? this->f == this->f : this->c == rhs.c);
    }

    bool operator!=(const token& rhs) const { return !(*this == rhs); }
};

vector<token> tokenize_expression(const string& input);
