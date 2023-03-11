#include "impl.hh"

Int getInt(istream &in)
{
  static char slask;
  while(not (in.eof() or isdigit(in.peek()) or in.peek()=='-'))
    in>>slask;
  Int ret;
  in>>ret;
  return ret;
}

vector<Sensor> getData(string filename)
{
  vector<Sensor> ret;
  ifstream in(filename);
  while(true)
      try{
	ret.emplace_back(Sensor(in));
      }catch(...){
	return ret;
      }
}

Int countOn(Int const activeSensors,
	    Int const startIndex,
	    auto const begin,
	    auto const end)
{
  if(begin==end)
    return 0;

  assert(activeSensors>=0);

  Int increase;
  if(activeSensors==0)
    increase = 0;
  else
    increase = ( begin->first - startIndex );

  
  return increase + countOn( activeSensors + begin->second,
			     begin->first,
			     next(begin),
			     end );
}

Int countOn(map<Int, int> const &onOff)
{
  auto start = onOff.begin();
  return  countOn(start->second,
		  start->first,
		  next(start),
		  onOff.end());
		  
}

Int beaconsOnRow(vector<Sensor> const &sensors, Int row)
{
  return count_if(sensors.begin(),
		  sensors.end(),
		  [row](auto const &s){
		    return s.x==row;
		  });
}

Int crapOnRow(vector<Sensor> const &sensors, Int row)
{
  set<array<int,2>> beacons;
  for(auto const &s: sensors)
    if(s.by==row)
      beacons.insert({s.bx, s.by});
  return beacons.size();
}

map<Int, int> getOnOff(vector<Sensor> const &sensors, Int row)
{
  map<Int, int> onOff;
  for(auto const & s: sensors)
    {
      auto halfLength = s.r - abs(row-s.y);
      if( halfLength >=0 )
	{
	  onOff[s.x-halfLength  ]++; //Turn on
	  onOff[s.x+halfLength+1]--; //Turn off
	}
    }
  return onOff;
}

Int watchedLocationsCount(vector<Sensor> const &sensors, Int row)
{

  return countOn(getOnOff(sensors, row)) - crapOnRow(sensors, row);
}

Int solutionA(string filename, Int row)
{
  return watchedLocationsCount(getData(filename), row)
    ;
}
