#include "player.hh"
#include <cassert>
void Player::move(unsigned int v)
{
  pos_+=v;
  score_+=pos();
}

unsigned int Player::score() const
{
  return score_;
}

Player::Player(unsigned int pos, unsigned int score)
  :pos_(pos-1)
  ,score_(score)
{
  assert(this->pos()>=1);
  assert(this->pos()<=maxPos);
}

unsigned int Player::pos() const
{
  if((pos_+1)>maxPos)
    pos_%=maxPos;
  return 1+pos_;
}

bool operator<(Player const &a, Player const &b)
{
  if(a.pos()<b.pos())
    return true;
  else if (a.pos()>b.pos())
    return false;
  else if(a.score()<b.score())
    return true;
  // else if (a.score()>b.score())
  //   return false;
  else
    return false;
}
