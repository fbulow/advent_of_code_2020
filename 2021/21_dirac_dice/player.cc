#include "player.hh"
void Player::move(unsigned int v)
{
  pos_+=v;
  score_+=pos();
}

unsigned int Player::score() const
{
  return score_;
}

Player::Player(unsigned int pos)
  :pos_(pos-1)
{}

unsigned int Player::pos() const
{
  if((pos_+1)>maxPos)
    pos_%=maxPos;
  return 1+pos_;
}
