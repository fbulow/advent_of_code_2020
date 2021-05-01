#include <gtest/gtest.h>
#include "gmock/gmock.h"

// As you approach Neptune, a planetary security system detects you and activates a giant tractor beam on Triton! You have no choice but to land.

// A scan of the local area reveals only one interesting feature: a massive underground vault. You generate a map of the tunnels (your puzzle input). The tunnels are too narrow to move diagonally.

// Only one entrance (marked @) is present among the open passages (marked .) and stone walls (#), but you also detect an assortment of keys (shown as lowercase letters) and doors (shown as uppercase letters). Keys of a given letter open the door of the same letter: a opens A, b opens B, and so on. You aren't sure which key you need to disable the tractor beam, so you'll need to collect all of them.

// For example, suppose you have the following map:

// #########
// #b.A.@.a#
// #########

// Starting from the entrance (@), you can only access a large door (A) and a key (a). Moving toward the door doesn't help you, but you can move 2 steps to collect the key, unlocking A in the process:

#include"vault.hpp"

TEST(Vault, example_initial)
{
  Vault sut({
      "#########"
      "#b.A.@.a#"
      "#########"
    });
  ASSERT_EQ(1,
            sut.destinations().size());
  ASSERT_EQ('a',
            sut.destinations()[0].name);
}


TEST(Vault, example_initial_options)
{
  auto sut = options( Vault({
        "#########"
        "#b.A.@.a#"
        "#########"
      }) );
  ASSERT_EQ('a',
            sut.begin()->name);
  ASSERT_EQ(2,
            sut.begin()->steps);
}




// #########
// #b.....@#
// #########

TEST(Vault, no_snabela_false)
{
  Vault sut({
      "#########"
      "#b.....@#"
      "#########"
    });
  ASSERT_FALSE(sut.no_snabela());
}

TEST(Vault, no_snabela_true)
{
  Vault sut({
      "#########"
      "#b.....##"
      "#########"
    });
  ASSERT_TRUE(sut.no_snabela());
}


TEST(Vault, example_initial_second_move)
{
  Vault sut({
      "#########"
      "#b.....@#"
      "#########"
    });
  ASSERT_EQ(1,
            sut.destinations().size());
  ASSERT_EQ('b',
            sut.destinations()[0].name);


}

TEST(Vault, a_step)
{
  Vault sut({
      "#########",
      "#b.....@#",
      "#########"
    });

  sut.step();
  ASSERT_TRUE(sut==
              Vault({
                  "#########",
                  "#b....@##",
                  "#########"
                }));
}

TEST(Vault, a_step_find)
{
  auto sut = Vault({
      "#########",
      "#b@.#####",
      "#########"
    }).step();

  ASSERT_TRUE(find(sut.begin(), sut.end(), 'b')!=sut.end());
}


// Then, you can move 6 steps to collect the only other key, b:

// #########
// #@......#
// #########

// So, collecting every key took a total of 8 steps.


// Here is a larger example:

// ########################
// #f.D.E.e.C.b.A.@.a.B.c.#
// ######################.#
// #d.....................#
// ########################

// The only reasonable move is to take key a and unlock door A:

// ########################
// #f.D.E.e.C.b.....@.B.c.#
// ######################.#
// #d.....................#
// ########################

// Then, do the same with key b:

// ########################
// #f.D.E.e.C.@.........c.#
// ######################.#
// #d.....................#
// ########################

// ...and the same with key c:

// ########################
// #f.D.E.e.............@.#
// ######################.#
// #d.....................#
// ########################

// Now, you have a choice between keys d and e. While key e is closer, collecting it now would be slower in the long run than collecting key d first, so that's the best choice:

TEST(two, options)
{
  Vault sut({
      "########################",
      "#f.D.E.e.............@.#",
      "######################.#",
      "#d.....................#",
      "########################"});

  set<Destination> ans{{'e'}, {'d'}};
  ASSERT_EQ(ans,
            options(sut));
}

// ########################
// #f...E.e...............#
// ######################.#
// #@.....................#
// ########################

// Finally, collect key e to unlock door E, then collect key f, taking a grand total of 86 steps.

// Here are a few more examples:

//     ########################
//     #...............b.C.D.f#
//     #.######################
//     #.....@.a.B.c.d.A.e.F.g#
//     ########################

//     Shortest path is 132 steps: b, a, c, d, f, e, g

//     #################
//     #i.G..c...e..H.p#
//     ########.########
//     #j.A..b...f..D.o#
//     ########@########
//     #k.E..a...g..B.n#
//     ########.########
//     #l.F..d...h..C.m#
//     #################

//     Shortest paths are 136 steps;
//     one is: a, f, b, j, g, n, h, d, l, o, e, p, c, i, k, m

//     ########################
//     #@..............ac.GI.b#
//     ###d#e#f################
//     ###A#B#C################
//     ###g#h#i################
//     ########################

//     Shortest paths are 81 steps; one is: a, c, f, i, d, g, b, e, h

// How many steps is the shortest path that collects all of the keys?
