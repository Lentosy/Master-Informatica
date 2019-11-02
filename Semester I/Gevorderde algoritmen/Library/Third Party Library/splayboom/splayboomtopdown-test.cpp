
// #include "splayboomtopdown.h"

// #include "gtest/gtest.h"

// class SplayboomTopDownTest : public ::testing::Test
// {
// protected:
//     void SetUp() override
//     {
//         test_boom.voeg_toe(8, 0);
//         test_boom.voeg_toe(3, 0);
//         test_boom.voeg_toe(1, 0);
//         test_boom.voeg_toe(6, 0);
//         test_boom.voeg_toe(10, 0);
//         test_boom.voeg_toe(9, 0);
//         test_boom.voeg_toe(14, 0);
//         test_boom.voeg_toe(13, 0);
//     }

//     void TearDown() override
//     {
//     }

//     SplayboomTopDown<int, int> test_boom;
// };

// TEST_F(SplayboomTopDownTest, constructor)
// {
//     // ASSERT_EQ(
//     //         test_boom.to_string(),
//     //         "((((((NULL <- 1 -> (NULL <- 3 -> NULL)) <- 6 -> NULL) <- 8 -> NULL) <- 9 -> NULL) <- 10 -> NULL) <- 13 -> (NULL <- 14 -> NULL))");
// }

// // http://www.cs.usfca.edu/~galles/visualization/SplayTree.html
// TEST_F(SplayboomTopDownTest, zoek)
// {
//     test_boom.zoek(2);

//     // ASSERT_EQ(
//     //         test_boom.to_string(),
//     //         "((NULL <- 1 -> NULL) <- 3 -> (((NULL <- 6 -> NULL) <- 8 -> (NULL <- 9 -> NULL)) <- 10 -> (NULL <- 13 -> (NULL <- 14 -> NULL))))");

//     test_boom.zoek(8);

//     // ASSERT_EQ(
//     //         test_boom.to_string(),
//     //         "(((NULL <- 1 -> NULL) <- 3 -> (NULL <- 6 -> NULL)) <- 8 -> ((NULL <- 9 -> NULL) <- 10 -> (NULL <- 13 -> (NULL <- 14 -> NULL))))");
// }
