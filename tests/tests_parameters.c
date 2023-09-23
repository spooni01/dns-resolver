#include <gtest/gtest.h>
#include "../src/main.c"

TEST(Parametre, getParams) {
    // dns [-r] [-x] [-6] -s server [-p port] address
    int argc = 8;
    char argv[] = {"-r", "-x", "-6", "-s", "kazi.fit.vutbr.cz", "-p", "20", "www.fit.vut.cz"};
    EXPECT_NO_THROW(getParams(argc, argv));
    //EXPECT_ANY_THROW(getParams(1, "-a"));
}

