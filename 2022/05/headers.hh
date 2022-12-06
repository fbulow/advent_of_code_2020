#include <AoC/getAllLines.hh>
#include <numeric>
#include <algorithm>
#include <stack>
#include <sstream>

using namespace std;

char getStack(int stackNr, string const &s);
bool isNumbersRow(string const & row);

vector<string>::iterator numbersRow(vector<string> input);
int vectorSize(vector<string> const &input);
int vectorSize(string const &numbersRow);
