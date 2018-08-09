#include "../lib/version.h"
#include "gtest/gtest.h"
#include "../inc/factorial.h"
#include "../inc/allocator.h"

struct test_class {
    test_class() {  std::cout << "ctor" << std::endl;  ctor_called = true; };

    ~test_class() { dtor_called = true; };

    bool is_ctor_called() { return ctor_called; }

    bool is_dtor_called() { return dtor_called; }

private:
    bool ctor_called = false;
    bool dtor_called = false;
};

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
    EXPECT_EQ(factorial(10), 3628800);
    EXPECT_EQ(factorial(11), 39916800);
    EXPECT_EQ(factorial(12), 479001600);
    EXPECT_EQ(factorial(13), 6227020800);
    EXPECT_EQ(factorial(14), 87178291200);
    EXPECT_EQ(factorial(15), 1307674368000);
    EXPECT_EQ(factorial(16), 20922789888000);
    EXPECT_EQ(factorial(17), 355687428096000);
    EXPECT_EQ(factorial(18), 6402373705728000);
    EXPECT_EQ(factorial(19), 121645100408832000);
    EXPECT_EQ(factorial(20), 2432902008176640000);
}

//TEST(allocator, size) {
//    constexpr unsigned int n = 10;
//    using type = test_class;
//
//    custom::allocator<type, n> allocator;
//    EXPECT_EQ(sizeof(allocator), sizeof(type) * n + sizeof(std::bitset<n>));
//}

//TEST(allocator, allocate_one_element) {
//    using type = test_class;
//    constexpr auto n = 1;
//    using allocator_t = custom::allocator<type, n>;
//
//    type *element = nullptr;
//    try {
//        allocator_t allocator;
//        element = allocator.allocate(n);
//    }
//    catch (const std::bad_alloc &e) {
//        FAIL() << e.what();
//    }
//
//    EXPECT_NE(element, nullptr);
//}
//
//TEST(allocator, allocate_more_elements) {
//    using type = test_class;
//    constexpr auto n = 1;
//    using allocator_t = custom::allocator<type, n>;
//
//    auto is_alloc_fail = false;
//    try {
//        allocator_t allocator;
//        allocator.allocate(n + 1);
//    }
//    catch (const std::bad_alloc &e) {
//        is_alloc_fail = true;
//    }
//
//    EXPECT_TRUE(is_alloc_fail);
//}
//
//TEST(allocator, deallocate_true_element) {
//    using type = test_class;
//    constexpr auto n = 1;
//    using allocator_t = custom::allocator<type, n>;
//
//    try {
//        allocator_t allocator;
//        auto element = allocator.allocate(n);
//        allocator.deallocate(element, n);
//    }
//    catch (const std::bad_alloc &e) {
//        FAIL() << e.what();
//    }
//}
//
//TEST(allocator, deallocate_fake_element) {
//    using type = test_class;
//    constexpr auto n = 1;
//    using allocator_t = custom::allocator<type, n>;
//
//    auto is_deallocate_fail = false;
//    try {
//        allocator_t allocator;
//        auto element = allocator.allocate(n);
//        allocator.deallocate(element + 1, n);
//    }
//    catch (const std::bad_alloc &e) {
//        is_deallocate_fail = true;
//    }
//
//    EXPECT_TRUE(is_deallocate_fail);
//}
//
//TEST(allocator, deallocate_fake_num) {
//    using type = test_class;
//    constexpr auto n = 1;
//    using allocator_t = custom::allocator<type, n>;
//
//    auto is_deallocate_fail = false;
//    try {
//        allocator_t allocator;
//        auto element = allocator.allocate(n);
//        allocator.deallocate(element, n + 1);
//    }
//    catch (const std::bad_alloc &e) {
//        is_deallocate_fail = true;
//    }
//
//    EXPECT_TRUE(is_deallocate_fail);
//}
//
//TEST(allocator, construct) {
//    using type = test_class;
//    constexpr auto n = 1;
//    using allocator_t = custom::allocator<type, n>;
//
//    try {
//        allocator_t allocator;
//        auto element = allocator.allocate(n);
//        allocator.construct(element);
//        EXPECT_TRUE(element->is_ctor_called());
//    }
//    catch (const std::bad_alloc &e) {
//        FAIL() << e.what();
//    }
//}

TEST(allocator, destruct) {
    using type = test_class;
    constexpr auto n = 5;
    constexpr auto value = 123;
    using allocator_t = custom::allocator<type, n>;

    try {
        auto *allocator = new allocator_t;
        auto element = allocator->allocate(n);
        // TODO: двойной вызов конструктора.
        allocator->construct(element);
        allocator->destroy(element);
    }
    catch (const std::bad_alloc &e) {
        FAIL() << e.what();
    }
}


int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}