#include "test.hpp"

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  auto ret = RUN_ALL_TESTS();
  if(ret!=0)
    return ret;
  else
    {
      auto data = input(cin);
      cout<<"a: "<<solution_a(data)<<endl
          <<"b: "<<solution_b(data)<<endl;
    }
}

