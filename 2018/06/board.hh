#pragma once
#include"input.hh"
#include<vector>
#include<limits>
#include<set>
#include<iostream>
#include<string_view>
#include"char_convert.hh"
using namespace std;
class BoardAsVectors : public vector<vector<int>>
{
public:
  BoardAsVectors()=default;
  BoardAsVectors(size_t s):vector<vector<int>>(s){}
  BoardAsVectors(vector<vector<int>> && data)
    :vector<vector<int>>(move(data))
  {}
  BoardAsVectors(vector<string_view> const &strings)
  {
    assert(strings.size()>0);
    reserve(strings.size());
    auto const n = strings.begin()->size();
    for(auto const &x : strings)
      {
	vector<int> row;
	row.resize(n);
	transform(x.begin(),
		  x.end(),
		  row.begin(),
		  fromVisibleChar);
	emplace_back(move(row));
      }
  }
  int get(int row, int col)
  {
    return (*this)[row][col];
  }

};

class Board{
public:
  Board(Data d);
  Board(BoardAsVectors &&data);
  template<typename ... T>
  Board(T && ...  x)
    :Board(BoardAsVectors({std::forward<T>(x)...}))
  {}
     
    

  int get(int row, int col)
  {
    return data[row][col];
  }
  
  
  void fill()
  {
    
  }
  int sizeOfLargestFiniteRegion();
  set<int>infiniteRegions();
  
  vector<int> regionSizes()
  {
    auto infinite = numeric_limits<int>::max();
    return {1, 99, infinite, 9, 17, infinite}; //TODO
  }
  int nRows() const{return data.size();}
  int nCols() const{return data[0].size();}
  
private:
  friend ostream& operator<<(ostream& out, Board const &b);
  BoardAsVectors data;
};

ostream& operator<<(ostream& out, Board const &b);

