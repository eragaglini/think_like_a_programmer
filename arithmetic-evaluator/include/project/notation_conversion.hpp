#include "project/expression_tokenizer.hpp"
#include <string>
#include <vector>

using namespace std;

vector<token> infix_to_postfix(const vector<token>& tokens);
