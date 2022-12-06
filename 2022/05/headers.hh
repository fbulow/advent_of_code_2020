#include <AoC/getAllLines.hh>
#include <numeric>
#include <algorithm>
#include <stack>
#include <sstream>

using namespace std;

char getStack(int stackNr, string const &s);
bool isNumbersRow(string const & row);

size_t numbersRow (vector<string> const & input);
int vectorSize(vector<string> const &input);
int vectorSize(string const &numbersRow);

struct Command{
  int count;
  int from;
  int to;
  Command(string const row);
};
