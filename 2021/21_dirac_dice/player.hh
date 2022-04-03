#pragma once

class Player
{
  mutable unsigned int pos_;
  unsigned int score_{0};
public:
  unsigned int pos() const;
  Player(unsigned int pos);
  static constexpr auto maxPos = 10;
  void move(unsigned int v);
  unsigned int score() const;
};
