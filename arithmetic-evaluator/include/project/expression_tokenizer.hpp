#include <string>
#include <vector>

using namespace std;

bool is_operator(char ch);

int get_precedence(char ch);

struct token
{
    char c;
    float f;
    bool number;

    token() : number(false), c(0) {};
    token(char c, bool number, float f) : c(c), number(number), f(f) {}
    char to_char() { return this->number ? this->f : this->c; }
    bool operator==(const token& rhs) const
    {
        return this->number == rhs.number &&
               (this->number ? this->f == rhs.f
                             : this->c == rhs.c);
    }

    bool operator!=(const token& rhs) const { return !(*this == rhs); }
    bool operator<(const token& rhs) const
    {
        if (this->number && rhs.number) {
            return this->f < rhs.f;
        } else if (!this->number && !rhs.number) {
            return get_precedence(this->c) < get_precedence(rhs.c);
        } else {
            // one is a number and the other is an operator, numbers come first
            return this->number;
        }
    }
    bool operator>(const token& rhs) const { return rhs < *this; }
    bool operator<=(const token& rhs) const { return !(*this > rhs); }
    bool operator>=(const token& rhs) const { return !(*this < rhs); }
};

vector<token> tokenize_expression(const string& input);

string token_vector_to_string(const vector<token> & tokens);
