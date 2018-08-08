#include "../lib/version.h"
#include "gtest/gtest.h"
#include "../inc/factorial.h"
#include "../inc/allocator.h"

TEST(lib, version) {
    EXPECT_GT(version(), 0);
}

TEST(factorial, factorial) {
    EXPECT_EQ(factorial(0), 1);
    EXPECT_EQ(factorial(1), 1);
    EXPECT_EQ(factorial(2), 2);
    EXPECT_EQ(factorial(3), 6);
    EXPECT_EQ(factorial(4), 24);
    EXPECT_EQ(factorial(5), 120);
    EXPECT_EQ(factorial(6), 720);
    EXPECT_EQ(factorial(7), 5040);
    EXPECT_EQ(factorial(8), 40320);
    EXPECT_EQ(factorial(9), 362880);
    EXPECT_EQ(factorial(10),3628800);
    EXPECT_EQ(factorial(11),39916800);
    EXPECT_EQ(factorial(12),479001600);
    EXPECT_EQ(factorial(13),6227020800);
    EXPECT_EQ(factorial(14),87178291200);
    EXPECT_EQ(factorial(15),1307674368000);
    EXPECT_EQ(factorial(16),20922789888000);
    EXPECT_EQ(factorial(17),355687428096000);
    EXPECT_EQ(factorial(18),6402373705728000);
    EXPECT_EQ(factorial(19),121645100408832000);
    EXPECT_EQ(factorial(20),2432902008176640000);
}

TEST(allocator, size) {
    constexpr unsigned int n = 10;
    using type = int;

    custom::allocator<type, n> allocator;
    EXPECT_EQ(sizeof(allocator), sizeof(type) * n + sizeof(std::bitset<n>));
}

TEST(allocator, allocate_one_element) {
    // TODO: Добавить проверку.
    EXPECT_EQ(1,0);
}

TEST(allocator, allocate_more_elements) {
    // TODO: Добавить проверку.
    EXPECT_EQ(1,0);
}

TEST(allocator, deallocate_true_element) {
    // TODO: Добавить проверку.
    EXPECT_EQ(1,0);
}

TEST(allocator, deallocate_fake_element) {
    // TODO: Добавить проверку.
    EXPECT_EQ(1,0);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}