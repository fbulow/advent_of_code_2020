#include <gtest/gtest.h>
#include "main.cpp"
#include "gmock/gmock.h"

TEST(Food, examples)
{
  {
    Food sut("mxmxvkd kfcds sqjhc nhms (contains dairy, fish)");
    auto ref = Allergens({"dairy", "fish"});
    EXPECT_EQ(ref, sut.allergens);
  }
  {
    Food sut("trh fvjkl sbzzf mxmxvkd (contains dairy)");
    auto ref = Allergens({"dairy"});
    EXPECT_EQ(ref, sut.allergens);
  }

  {
    Ingredients sut("trh fvjkl sbzzf mxmxvkd (contains dairy)");
    set<string> ref{"trh", "fvjkl", "sbzzf", "mxmxvkd"};
    EXPECT_EQ(ref, sut);
  }
  {
    Ingredients sut("trh fvjkl sbzzf mxmxvkd");
    set<string> ref{"trh", "fvjkl", "sbzzf", "mxmxvkd"};
    EXPECT_EQ(ref, sut);
  }
  
}

TEST(countSafeIngredients, example)
{
  ASSERT_EQ(5, countSafeIngredients(allFood(EXAMPLE), {"kfcds", "nhms", "sbzzf", "trh"}));
}

TEST(getSafeIngredients, example)
{
  set<string> ref{"kfcds", "nhms", "sbzzf", "trh"};
  ASSERT_EQ(ref, getSafeIngredients(allFood(EXAMPLE)));
}

TEST(solution, a)
{
  ASSERT_EQ(5, solutionA(EXAMPLE));
  cout<<"Solution a: "<<solutionA(INPUT)<<endl;
}


TEST(example, cannonical_list)
{
  ASSERT_EQ("mxmxvkd,sqjhc,fvjkl", solutionB(EXAMPLE));
  cout<<"Solution B: "<< solutionB(INPUT) << endl;
}
