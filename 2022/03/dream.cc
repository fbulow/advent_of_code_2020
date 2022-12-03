

int solA()
{
  
  return sumUp(commonLetters(getLines<string>()));

}

string commonLetters(lines)
{
  string ret;
  ret.resize(lines.size());
  for(x:lines)
    {
      middle = advance(line.begin(), line.size()/2);
      
      compartmentA = set({x.begin(), middle});

      filter(middle, x.end(),
	     ret.begin(),
	     [compartmentA](char c) ->bool
	     {
	       return compartmentA.contains(c);
	     });
    }
  return ret;
}

int sumUp(string)
{

}
