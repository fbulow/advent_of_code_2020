#pragma once


struct ScanSpace{
  Beacons beacons;
  Coord scanner{0,0,0};
  bool absoluteCoordinates{false};
  ScanSpace(Beacons const &beacons)
    :beacons(beacons)
  {}
  
  ScanSpace(ScanSpace const & other, auto transformation)
  {
    beacons.resize(other.beacons.size());
    scanner = transformation(other.scanner);
    transform(other.beacons.cbegin(),
              other.beacons.cend(),
              beacons.begin(),
              transformation);
      
  }
  bool inScannerRange(Coord const &p) const // True of p is within reach of any scanner.
  {
    return ::inScannerRange(scanner, p);
  }
  bool contains(Coord const &beacon) const
  {
    return find(beacons.cbegin(),
                beacons.cend(),
                beacon) != beacons.cend();
  }
};

