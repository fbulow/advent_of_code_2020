#include "monkey.hh"
using namespace std;

vector<Monkey> Monkey::input()
{
  return {
    Monkey([](WorryValue old){return old * 3;},
	   13,
	   6,
	   2,
	   89, 73, 66, 57, 64, 80),
    Monkey([](WorryValue old){return old + 1;},
	   3,
	   7,
	   4,
	   83, 78, 81, 55, 81, 59, 69),

    Monkey([](WorryValue old){return old * 13;},
	   7,
	   1,
	   4,
	   76, 91, 58, 85),

    Monkey([](WorryValue old){return  old * old;},
	   2,
	   6,
	   0,
	   71, 72, 74, 76, 68),

    Monkey([](WorryValue old){return  old + 7;},
	   19,
	   5,
	   7,
	   98, 85, 84),


    Monkey(
	   [](WorryValue old){return  old + 8;},
	   5,
	   3,
	   0,
	   78),

    Monkey(
	   [](WorryValue old){return  old + 4;},
	   11,
	   1,
	   2,
	   86, 70, 60, 88, 88, 78, 74, 83),
    Monkey([](WorryValue old){return  old + 5;},
	   17,
	   3,
	   5,
	   81, 58)
  };
}
vector<Monkey> Monkey::example()
{
  return {
    Monkey([](WorryValue old){return old * 19;},
	   23,
	   2,
	   3,79,98),
    Monkey([](int old){return old + 6;},
	   19,
	   2,
	   0,
	   54, 65, 75, 74),
    Monkey([](int old){return old * old;},
	   13,
	   1,
	   3,
	   79, 60, 97),
    Monkey(
	   [](int old){return old + 3;},
	   17,
	   0,
	   1,
	   74)
  };
}

void round(std::vector<Monkey> & data, Counter &c)
{
  for(size_t i=0;i<data.size();i++)
    while(not data[i].empty())
      {
	auto p = data[i].pop();
	data[p.destination].push(p.value);
	c.tick(i);
      }
}
