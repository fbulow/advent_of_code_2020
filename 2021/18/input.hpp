#pragma once

using Data = vector<string>;

Data input(istream& cin)
{
  Data ret;
  string s;
  cin>>s;
  while(not cin.eof())
    {
      ret.push_back(s);
      cin>>s;
    }
  return ret;
}

TEST(input, all)
{
  istringstream in("Hello\nworld");
  EXPECT_EQ("Hello", input(in)[0]);
}

