#include <gtest/gtest.h>
#include "../src/main.c"

TEST(Parametre, getParams) {
    // dns [-r] [-x] [-6] -s server [-p port] address
    int argc = 8;
    char argv[] = {"-r", "-x", "-6", "-s", "kazi.fit.vutbr.cz", "-p", "20", "www.fit.vut.cz"};
    EXPECT_NO_THROW(getParams(argc, argv));

    int argc = 3;
    char argv[] = {"-s", "kazi.fit.vutbr.cz", "www.fit.vut.cz"};
    EXPECT_NO_THROW(getParams(argc, argv));

    int argc = 7;
    char argv[] = {"-x", "-6", "-s", "kazi.fit.vutbr.cz", "-p", "20", "www.fit.vut.cz"};
    EXPECT_NO_THROW(getParams(argc, argv));

    int argc = 7;
    char argv[] = {"-r", "-6", "-s", "kazi.fit.vutbr.cz", "-p", "20", "www.fit.vut.cz"};
    EXPECT_NO_THROW(getParams(argc, argv));

    int argc = 7;
    char argv[] = {"-r", "-x", "-s", "kazi.fit.vutbr.cz", "-p", "20", "www.fit.vut.cz"};
    EXPECT_NO_THROW(getParams(argc, argv));

    int argc = 6;
    char argv[] = {"-r", "-x", "-6", "-s", "kazi.fit.vutbr.cz", "www.fit.vut.cz"};
    EXPECT_NO_THROW(getParams(argc, argv));

    int argc = 6;
    char argv[] = {"-r", "-x", "-6", "-p", "20", "www.fit.vut.cz"};
    EXPECT_ANY_THROW(getParams(argc, argv));

    int argc = 7;
    char argv[] = {"-r", "-x", "-6", "-s", "kazi.fit.vutbr.cz", "-p", "20"};
    EXPECT_ANY_THROW(getParams(argc, argv));

    int argc = 1;
    char argv[] = {"kazi.fit.vutbr.cz"};
    EXPECT_ANY_THROW(getParams(argc, argv));

    int argc = 0;
    char argv[] = {};
    EXPECT_ANY_THROW(getParams(argc, argv));

}

