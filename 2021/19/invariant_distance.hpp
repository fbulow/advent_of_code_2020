#pragma once

struct InvariantDistance{
  unsigned int const dMax;
  unsigned int const dMed;
  unsigned int const dMin;
  InvariantDistance(Coord const & a, Coord const & b);
  bool operator==(InvariantDistance const& other) const;
};


struct InvariantSpace : public ScanSpace{
  //All (beacon) indexes that can be reached by travelling Distance from any other (beacon) index.
  map<InvariantDistance, set<size_t>> DistnaceToIndexes;

  InvariantSpace(Beacons const &beacons)
    :ScanSpace(beacons)
  {}
  
  ScanSpace(ScanSpace const & other, auto transformation)

};

struct BestCandidates{
  size_t knownIndex;
  set<size_t> unknownIndex;
  BestCandidates(InvariantSpace const& known, InvariantSpace const& unknown);
};
