#include"include.hh"

void floodFill(FromToMinutesCallback ret,
	       Input const &data,
	       Valve const &startAt,
	       Minutes const total
	       )
{
  floodFillRec(
     [startAt, &ret, total]
     (Valve v, Minutes m)
     {
       ret(startAt, v, 1+total - m);
     },
     [data]
     (Valve const &v)
     {return data.adjacent(v);},
     Regions(data.allValves()).moveTo(startAt),
     total
     );
}
	  

class FillCache
{
  /* Holds regions for each starting point
   */
  
};





// TEST(PathGeneratorImpl, example_DD_or_BB)
// {
//   //  PathGeneratorImpl(example())
// }

// TEST(distance_cache, jj_to_ii)
// {
//   auto sut = 
//     Distance( example(),
// 	      "JJ",
// 	      3
// 	      );
  
//   {
//     auto ans = sut.from(Valve("JJ"), Steps(1));

//     EXPECT_EQ(ans.size(), 1);
//     EXPECT_TRUE(ans.contains(ValveConnection("JJ", "II", 1)));
//   }
// }
//   {
//     auto ans = sut.from(Valve("JJ"), Steps(2));

//     EXPECT_EQ(ans.size(), 2);
//     EXPECT_TRUE(ans.contains(ValveConnection("JJ", "II", 1)));
//     EXPECT_TRUE(ans.contains(ValveConnection("JJ", "AA", 2)));
//   }
// }
