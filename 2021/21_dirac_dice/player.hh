#pragma once

class Player
{
  mutable unsigned int pos_;
  unsigned int score_{0};
public:
  unsigned int pos() const;
  Player(unsigned int pos, unsigned int score=0);
  static constexpr auto maxPos = 10;
  void move(unsigned int v);
  unsigned int score() const;
};

bool operator<(Player const &a, Player const &b);
