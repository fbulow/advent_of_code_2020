#pragma once
#include "coord.hpp"
#include "scan_space.hpp"

bool check_match(ScanSpace const &known, ScanSpace const &unknown)
{
  assert(known.absoluteCoordinates);
  assert(not unknown.absoluteCoordinates);
  unsigned int scannerCount{0};
  
  for(auto const & u:unknown.beacons)
    {
      if(known.inScannerRange(u)) // seen by both.
        {
          if (not known.contains(u))
            return false;
          else
            scannerCount++;
        }
    }
  /* By finding pairs of scanners that both see at least 12 of the
     same beacons, you can assemble the entire map. 
   */
  return scannerCount>=12;
}

TEST(example, confirm_match)
{
  auto cin = example_istream();
  auto sut = input(cin);
  //Because of this, scanner 1 must be at 68,-1246,-43 (relative to scanner 0).

  ScanSpace a = sut[0];
  
  EXPECT_TRUE(a.contains({-618,-824,-621}));

  auto accepted_orientations = 0;
  int i=0;
  for(auto rot: orientations())
    {
      ScanSpace b(ScanSpace(ScanSpace{sut[1]},
                            rot),
                  translateFromTo({0,0,0}, {68,-1246,-43}));
      if( check_match(a,b) )
          accepted_orientations++;
      i++;
    }
  EXPECT_EQ(1, accepted_orientations);
}

optional<ScanSpace> find_match(ScanSpace const &known, ScanSpace const &unknown)
{
  for(auto k: known.beacons)
    {
      for(auto rot: orientations())
        //auto rot= orientations()[12];
      {
        ScanSpace b(unknown,rot);
        for(auto u: b.beacons)
        {
          ScanSpace ret(b,
                        translateFromTo(u, k)
                        );
          assert(ret.scanner!=Coord(0,0,0));
          if( check_match(known,ret) )
            {
              ret.absoluteCoordinates = true;
              return {ret};
            }
        }
      }
    }
  return {};
}

TEST(check_match, example)
{
  auto sut = input_example();
  EXPECT_TRUE (sut[0].absoluteCoordinates);
  EXPECT_FALSE(sut[1].absoluteCoordinates);
  EXPECT_TRUE(bool(find_match(sut[0], sut[1])));
  EXPECT_FALSE(bool(find_match(sut[0], sut[2])));
  //TODO use example match
}

bool isUnsolved(Data const &d)
{
  auto ret =  count_if(d.cbegin(),
                       d.cend(),
                       [](auto x){return not x.absoluteCoordinates;});
  return ret>0;
}

Data to_absolute(Data d)
{
  while(isUnsolved(d))
    {
      for(auto it = d.begin();it<d.end();advance(it,1))
        if(it->absoluteCoordinates)
          for(auto iu = d.begin();iu<d.end();advance(iu,1))
            if( it!=iu)
              if(not iu->absoluteCoordinates)
                {
                  auto nxt = find_match(*it, *iu);
                  if(nxt)
                    *iu = nxt.value();
                }
    }
  return d;
}
