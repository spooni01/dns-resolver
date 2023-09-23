#include <gtest/gtest.h>
#include "../src/main.c"

TEST(Parametre, getParams) {
    EXPECT_ANY_THROW(getParams(1, "-a"));
}

