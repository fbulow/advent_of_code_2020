#include <gtest/gtest.h>
#include "main.cpp"
#include "gmock/gmock.h"

TEST(Food, examples)
{
  {
    Food sut("mxmxvkd kfcds sqjhc nhms (contains dairy, fish)");
    auto ref = Allergens({"dairy", "fish"});
    EXPECT_EQ(ref, sut.allergens());
  }
  {
    Food sut("trh fvjkl sbzzf mxmxvkd (contains dairy)");
    auto ref = Allergens({"dairy"});
    EXPECT_EQ(ref, sut.allergens());
  }


  
}
