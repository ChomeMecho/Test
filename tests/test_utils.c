#include <stdio.h>
#include <stdlib.h>
#include "greatest.h"
#include "../utils.h"

TEST isalpha_str_alphastr_return1() {
    ASSERT_EQ(1, isalpha_str("abcd"));
    ASSERT_EQ(1, isalpha_str("ABCD"));
    ASSERT_EQ(1, isalpha_str("a"));
    ASSERT_EQ(1, isalpha_str("A"));
    ASSERT_EQ(1, isalpha_str(""));
    PASS();
}

TEST isalpha_str_alphastr_return0() {
    ASSERT_EQ(0, isalpha_str("abcd "));
    ASSERT_EQ(0, isalpha_str("ABCD "));
    ASSERT_EQ(0, isalpha_str(" "));
    ASSERT_EQ(0, isalpha_str("*"));
    PASS();
}

SUITE(test_utils) {
    RUN_TEST(isalpha_str_alphastr_return1);
    RUN_TEST(isalpha_str_alphastr_return0);
}

