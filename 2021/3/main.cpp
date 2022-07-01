#include "tests.cpp"

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  auto ret = RUN_ALL_TESTS();
  if(ret!=0)
    return ret;
  else
    cout<<"a: "<<solution_a(input())<<endl
        <<"b: "<<solution_b(input())<<endl;
}

