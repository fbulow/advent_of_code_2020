#include"headers.hh"

Command::Command(string const row)
{
  istringstream in(row);
  string slask;
  //move 1 from 2 to 3
  in>>
    slask >>count >> 
    slask >>from >> 
    slask >>to ;         
}





size_t numbersRow(vector<string> const & input)
{
  auto it = find_if(input.begin(),
		    input.end(),
		    isNumbersRow);


  assert(it!=input.end());
  return distance(input.begin(), it);
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
  return vectorSize(input[numbersRow(input)]);
}

char getStack(int stackNr, string const &s)
{
  auto index=(1==stackNr)?1:stackNr*4-3;
  
  if(index >= s.size())
     return '@';     
  else
    return s[index];
}
