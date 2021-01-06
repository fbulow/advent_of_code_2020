
struct  MonsterCoordinates :set<Coord> 
{
  int height;
  int width;
  MonsterCoordinates()
  {
    vector<string> const monster{
      "                  # ",
      "#    ##    ##    ###",
      " #  #  #  #  #  #   "};
    height=monster.size();
    assert(height>0);
    width =monster[0].size();
    assert(width>0);
    
    for(int i=0;i<monster.size();i++)
      {
        auto column = monster[i].find("#");
        while( column != string::npos )
          {
            insert({i, int(column)});
            column = monster[i].find("#", 1+column);
          }
      }
  }
};

unsigned int markMonsters(Collage& collage)
{
  unsigned int ret{0};
  auto monster = MonsterCoordinates();
  assert(monster.size()>0);
  for(int row = 0; row < collage.size() - monster.height ; row++)
    for(int column = 0; column < collage[0].size() - monster.width ; column++)
      {
        Coord c{row, column};
        auto mCoord = monster|views::transform([c, collage](Coord m){
          return Coord{c.row+m.row, c.column+m.column};});
        assert(mCoord.size() > 0);
        
        auto allHash = mCoord|views::transform([c, collage](Coord m){
          return '.'!=collage[m.row][m.column];
        });
        if(all_of(allHash.begin(), allHash.end(), [](bool x){return x;}))
          {
            ret++;
            for(auto m: mCoord)
                collage[m.row][m.column]='O';
          }
      }
  return ret;
}

unsigned int seaRoughness(Collage &c)
{
    auto positionCounter=0;
    while(positionCounter<20)
      {
        if(positionCounter%2==0)
          c.flip();
        else
          c.transpose();
        c.markMonsters();
        positionCounter++;
      }

  return accumulate(c.begin(),
                    c.end(),
                    (unsigned int) 0,
                    [](unsigned int sum, string const &s)
                    {
                      return sum+count_if(s.begin(),
                                          s.end(),
                                          [](char x)
                                          {
                                            return x=='#';
                                          }
                                          );
                    });
}
