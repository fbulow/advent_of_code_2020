#pragma once
#include<string>
#include<algorithm>
using namespace std;

int letter_count(char letter, std::string const &password)
{
  return std::count(password.begin(), password.end(), letter);
}
int letter_count(char const *letter, std::string const &password)
{
  return letter_count(*letter, password);
}
