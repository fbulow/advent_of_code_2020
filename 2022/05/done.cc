#include"headers.hh"

vector<string>::iterator numbersRow(vector<string> input)
{
  auto it = find_if(input.begin(),
		    input.end(),
		    isNumbersRow);


  assert(it!=input.end());
  return it;
}

bool isNumbersRow(string const & row)
{  return  (row[0]==' ') and (row[1]=='1');}


int numberOflargestStack(string const & row)
{
  istringstream in(row);

  int ret;
  in>>ret;
  while(not in.eof())
    in>>ret;
  return ret;
}


int vectorSize(int largetsStack)
{
  return largetsStack+1;
}

int vectorSize(string const &numbersRow)
{
  return vectorSize(numberOflargestStack(numbersRow));
}


int vectorSize(vector<string> const &input)
{
  return vectorSize(*numbersRow(input));
}

char getStack(int stackNr, string const &s)
{
    return s[stackNr==1?1:stackNr*4-3];
}
