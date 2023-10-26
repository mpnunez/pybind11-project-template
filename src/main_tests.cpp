#include <gtest/gtest.h>

using ::testing::InitGoogleTest;

// General notes:

// * Read the Google Test primer here:
//     https://github.com/google/googletest/blob/master/googletest/docs/primer.md
// * Underscores are forbidden in testcase and test names, due to macro
// preprocessor limitations in Google Test.

int main(int argc, char *argv[]) {
  InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
