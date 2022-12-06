#include"headers.hh"

bool isNumbersRow(string const & row)
{  return  (row[0]==' ') and (row[1]=='1');}

string numbersRow(vector<string> input)
{
  auto it = find_if(input.begin(),
		    input.end(),
		    isNumbersRow);


  assert(it!=input.end());
  return *it;
}


int vectorSize(string const &numbersRow)
{
  istringstream in(numbersRow);

  int ret;
  in>>ret;
  while(not in.eof())
    in>>ret;

  return ret+1;

}


int vectorSize(vector<string> const &input)
{
  return vectorSize(numbersRow(input));
}

char getStack(int stackNr, string const &s)
{
    return s[stackNr==1?1:stackNr*4-3];
}
