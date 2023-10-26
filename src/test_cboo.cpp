#include <gtest/gtest.h>

#include "intervalset.hpp"



TEST(operations, normalize) {
    IntervalSet iset3;
    iset3.insert(0,10);
    iset3.insert(5,15);
    iset3.insert(10,20);
    iset3.insert(15,25);
    iset3.sanitize();

    IntervalSet iset4;
    iset4.insert(0,25);

    ASSERT_EQ(iset3, iset4);
}

TEST(operations, union) {
    
    IntervalSet iset;
    iset.insert(1,4);
    iset.insert(8,12);
    iset.insert(15,20);

    IntervalSet iset2;
    iset2.insert(3,9);
    iset2.insert(11,12);

    IntervalSet expected;
    expected.insert(1,12);
    expected.insert(15,20);

    auto ans = iset | iset2;
    ASSERT_EQ(ans, expected);
}
TEST(operations, intersect) {

    IntervalSet iset;
    iset.insert(1,4);
    iset.insert(8,12);
    iset.insert(15,20);

    IntervalSet iset2;
    iset2.insert(3,9);
    iset2.insert(11,12);

    IntervalSet expected;
    expected.insert(3,4);
    expected.insert(8,9);
    expected.insert(11,12);

    auto ans = iset & iset2;
    ASSERT_EQ(ans, expected);
}
TEST(operations, not) {
    
    IntervalSet iset;
    iset.insert(1,4);
    iset.insert(8,12);
    iset.insert(15,20);

    IntervalSet iset2;
    iset2.insert(3,9);
    iset2.insert(11,12);

    IntervalSet expected;
    expected.insert(1,3);
    expected.insert(9,11);
    expected.insert(15,20);

    auto ans = iset - iset2;
    ASSERT_EQ(ans, expected);
}
TEST(operations, not2) {
    
    IntervalSet iset;
    iset.insert(1,4);
    iset.insert(8,12);
    iset.insert(15,20);

    IntervalSet iset2;
    iset2.insert(3,9);
    iset2.insert(11,12);

    IntervalSet expected;
    expected.insert(4,8);

    auto ans = iset2 - iset;
    ASSERT_EQ(ans, expected);
}
TEST(operations, xor) {

    IntervalSet iset;
    iset.insert(1,4);
    iset.insert(8,12);
    iset.insert(15,20);

    IntervalSet iset2;
    iset2.insert(3,9);
    iset2.insert(11,12);

    IntervalSet expected;
    expected.insert(1,3);
    expected.insert(4,8);
    expected.insert(9,11);
    expected.insert(15,20);

    auto ans = (iset ^ iset2);
    EXPECT_EQ(ans, expected);
}
