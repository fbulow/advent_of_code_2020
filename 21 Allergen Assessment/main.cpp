#include <fstream>
#include <string>
#include <vector>
// #include <cmath>
// #include <iostream>
// #include <limits>
#include <numeric>
// #include <cassert>
#include<list>
#include<deque>
#include <initializer_list>
#include <functional>
#include <boost/algorithm/string.hpp> 

using namespace std;

using I = unsigned long int;

struct Allergens :set<string>
{
  Allergens(initializer_list<string> &&x)
    :set<string>(move(x))
  {}
  
  Allergens(string const &s)
  {
    string commaSeparated = [&s](){//evaluated immediately
      string x=s.substr(s.find("(contains")+"(contains"s.size()+1);
      return x.substr(0,x.size()-1);
    }();

    deque<string> untrimmed;
    boost::split(untrimmed, commaSeparated, [](auto x){return x==',';});
    for(auto x:untrimmed)
      {
        boost::trim(x);
        insert(x);
      }
    
  }
};
struct Ingredients :set<string>
{
  Ingredients(string s)
  {
    deque<string> elemnts;
    boost::split(elemnts, s.substr(0, s.find("(contains")), [](char x){return x==' ';});
    for(auto x:elemnts)
      {
        boost::trim(x);
        if(not x.empty())
          insert(x);
      }
  }
};

struct Food
{
  Allergens allergens;
  Ingredients ingredients;
  Food(string const &s)
    :allergens(s)
    ,ingredients(s)
  {}
};


bool operator==(set<string> const &a, set<string> const &b)
{
  for(auto &x:a)
    if(not b.contains(x))
      return false;
  for(auto &x:b)
    if(not a.contains(x))
      return false;
  return true;
}

ostream& operator<<(ostream& out, Food const & f)
{
  for(auto &x:f.ingredients)
    out<<x<<" ";
  if(not f.allergens.empty())
    {
      out<<"(contains ";
      for(auto &x:f.allergens)
        out<<x<<", ";
    }
  return out;
}

unsigned int countSafeIngredients(deque<Food> const &allFood, set<string> const &safe)
{
  return accumulate(allFood.begin(),
                    allFood.end(),
                    (unsigned int) 0,
                    [&safe](auto sum, auto &x)
                    {
                      return sum+ count_if(x.ingredients.begin(),
                                           x.ingredients.end(),
                                           [&safe](auto &x)
                                           {
                                             return safe.contains(x);
                                           });
                    });
}

deque<Food> allFood(string filename)
{
  deque<Food> ret;
  ifstream in(filename);
  assert(in.is_open());
  string line;
  while(getline(in, line))
    {
      ret.emplace_back(Food(line));
    }
  return ret;
}

set<string> allIngredients(auto const & allFood)
{
  set<string> ret;
  for(auto &f: allFood)
    for (auto &i: f.ingredients)
      ret.insert(i);
  return ret;
}

using BadIngredients = map<string, set<string>>;
BadIngredients getBadIngredients(auto const & allFood)
{
  BadIngredients bad;
  for(auto const &f: allFood)
    {
      for(auto &a:f.allergens)
        {
          auto& cell = bad[a];
          if(cell.empty())
            cell = f.ingredients;
          else
            erase_if(cell,
                     [&f](auto &x){return not f.ingredients.contains(x);});
        }
    }
  return bad;
}

set<string> getSafeIngredients(auto const & allFood)
{
  auto bad = getBadIngredients(allFood);
  auto ret = allIngredients(allFood);
  for (auto [allergen, badIngredients] : bad)
    for(auto &i : badIngredients)
      ret.erase(i);
    
  return ret;
}

unsigned int solutionA(string filename)
{
  auto food = allFood(filename);
  return countSafeIngredients(food, getSafeIngredients(food));
}



string cannonicalAllergenList(BadIngredients b)
{
  set<string> known;

  auto updateKnown = [&known](BadIngredients const &b)
  {
    for(auto [a, i]: b)
      if(i.size()==1)
        known.insert(*i.begin());
  };


  auto isDone = [&b](){
    return all_of(b.begin(),
                  b.end(),
                  [](auto &x)
                  {
                    return x.second.size()==1;
                  });
                  
  };

  while(not isDone())
    {
      updateKnown(b);
      auto it = find_if(b.begin(), b.end(), [](auto &x){return x.second.size()!=1;});
      while(it!=b.end())
        {
          erase_if(it->second,
                   [known](string const &x){return known.contains(x);});
          it = find_if(next(it), b.end(), [](auto &x){return x.second.size()!=1;});
        }
    }

  string ret;
  for(auto &x:b)
    ret+=*x.second.begin()+",";
  return ret.substr(0, ret.size()-1);
}

string solutionB(string filename)
{
  return cannonicalAllergenList(getBadIngredients(allFood(filename)));
}
