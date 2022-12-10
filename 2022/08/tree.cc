#include "tree.hh"
Tree::Tree(char c)
  :value_(c)
{}
  
Tree::Tree(Tree const & t)
  :value_(t.value_)
  ,ticked_(t.ticked_)
{}
  
bool Tree::ticked() const {return ticked_;} 
char Tree::value()  const {return value_;} 
void Tree::tick(){ticked_=true;}

