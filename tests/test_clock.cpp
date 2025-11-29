#include <iostream>
#include <cstdlib>
#include "../tree/Clock.h"

#define EXPECT_EQ(got, want) \
    do { \
        auto g = (got); \
        auto w = (want); \
        if (g != w) { \
            std::cerr << "Test failed at line " << __LINE__ << ": " \
                      << "got " << (int)g << ", want " << (int)w << std::endl; \
            exit(1); \
        } \
    } while(0)

void test_getRandomPixel() {
    // starting values for pixels 0-2
    EXPECT_EQ(Clock::getRandomPixel(0, 0, 10), 0);
    EXPECT_EQ(Clock::getRandomPixel(0, 1, 10), 167);
    EXPECT_EQ(Clock::getRandomPixel(0, 2, 10), 152);


    // 10 ticks later for pixels 0-2
    EXPECT_EQ(Clock::getRandomPixel(100, 0, 10), 10);
    EXPECT_EQ(Clock::getRandomPixel(100, 1, 10), 177);
    EXPECT_EQ(Clock::getRandomPixel(100, 2, 10), 162);

    // when reach 255 for pixels 0-2
    EXPECT_EQ(Clock::getRandomPixel(2550, 0, 10), 255);
    EXPECT_EQ(Clock::getRandomPixel(880, 1, 10), 255);
    EXPECT_EQ(Clock::getRandomPixel(1030, 2, 10), 255);

    // confirm wrap around for pixels 0-2
    EXPECT_EQ(Clock::getRandomPixel(2570, 0, 10), 1);
    EXPECT_EQ(Clock::getRandomPixel(900, 1, 10), 1);
    EXPECT_EQ(Clock::getRandomPixel(1050, 2, 10), 1);

    std::cout << "test_getRandomPixel passed!" << std::endl;
}

int main() {
    test_getRandomPixel();
    return 0;
}
