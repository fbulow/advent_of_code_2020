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
using namespace std;

using I = unsigned long int;

I transform( I subjectNumber,  I loopSize, I value=1)
{
  //  The handshake used by the card and the door involves an
  //  operation that transforms a subject number. To transform a
  //  subject number, start with the value 1. Then, a number of times
  //  called the loop size, perform the following steps:
  //    - Set the value to itself multiplied by the subject number.
  //    - Set the value to the remainder after dividing the value by 20201227.

  for(I i=0;i<loopSize;i++)
    {
      value *= subjectNumber;
      value %= 20201227;
    }
  return value;
}

I getLoopSize(I publicKey, I subjectNumber = 7)
{
  I loopSize=1;
  auto value = transform(subjectNumber, 1, 1);
  while(value != publicKey)
    {
      value = transform(subjectNumber, 1, value);
      loopSize++;
    }
  return loopSize;
}


I solutionA(I pubDoor, I pubCard)
{
  auto doorKey = getLoopSize(pubDoor);
  return transform( pubCard, doorKey);
}
