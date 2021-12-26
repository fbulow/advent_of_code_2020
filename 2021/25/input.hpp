#pragma once

Data input(istream &in)
{
  vector<string> vs;
  string s;
  in>>s;
  while(not in.eof())
    {
      vs.push_back(s);
      in>>s;
    }
  return {vs};
}


TEST(example, small)
{
  {
    istringstream in("...>>>>>...\n");
    auto sut = input(in);
    sut.step();
    ASSERT_EQ("...>>>>.>..\n", sut.str());
    sut.step();
    ASSERT_EQ("...>>>.>.>.\n", sut.str());
  }
  {
    istringstream in(
                     "..........\n"
                     ".>v....v..\n"
                     ".......>..\n"
                     "..........\n");
    auto sut = input(in);
    sut.step();
    ASSERT_EQ(
              "..........\n"
              ".>........\n"
              "..v....v>.\n"
              "..........\n",
              sut.str());
  }
  
}
