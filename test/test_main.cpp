#include "../lib/version.h"
#include "gtest/gtest.h"
#include "../inc/factorial.h"
#include "../inc/allocator.h"
#include "../inc/container.h"

struct test_class {
    test_class() { ctor_called = true; };

    ~test_class() { dtor_called = true; };

    bool is_ctor_called() { return ctor_called; }

    bool is_dtor_called() { return dtor_called; }

    bool operator==(test_class &other) {
        return (other.ctor_called == ctor_called) && (other.dtor_called == dtor_called);
    }

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

TEST(allocator, size) {
    constexpr unsigned int n = 10;
    using type = test_class;
    auto radix = sizeof(void *);

    custom::allocator<type, n> allocator;

    auto data_size = ((sizeof(type) * n + radix - 1) / radix) * radix;
    auto bitset_size = sizeof(std::bitset<n>);
    EXPECT_EQ(sizeof(allocator), data_size + bitset_size);
}

TEST(allocator, allocate_one_element) {
    using type = test_class;
    constexpr auto n = 1;
    using allocator_t = custom::allocator<type, n>;

    type *element = nullptr;
    try {
        allocator_t allocator;
        element = allocator.allocate(n);
    }
    catch (const std::bad_alloc &e) {
        FAIL() << e.what();
    }

    EXPECT_NE(element, nullptr);
}

TEST(allocator, allocate_more_elements) {
    using type = test_class;
    constexpr auto n = 1;
    using allocator_t = custom::allocator<type, n>;

    auto is_alloc_fail = false;
    try {
        allocator_t allocator;
        allocator.allocate(n + 1);
    }
    catch (const std::bad_alloc &e) {
        is_alloc_fail = true;
    }

    EXPECT_TRUE(is_alloc_fail);
}

TEST(allocator, deallocate_true_element) {
    using type = test_class;
    constexpr auto n = 1;
    using allocator_t = custom::allocator<type, n>;

    try {
        allocator_t allocator;
        auto element = allocator.allocate(n);
        allocator.deallocate(element, n);
    }
    catch (const std::bad_alloc &e) {
        FAIL() << e.what();
    }
}

TEST(allocator, deallocate_fake_element) {
    using type = test_class;
    constexpr auto n = 1;
    using allocator_t = custom::allocator<type, n>;

    auto is_deallocate_fail = false;
    try {
        allocator_t allocator;
        auto element = allocator.allocate(n);
        allocator.deallocate(element + 1, n);
    }
    catch (const std::bad_alloc &e) {
        is_deallocate_fail = true;
    }

    EXPECT_TRUE(is_deallocate_fail);
}

TEST(allocator, deallocate_fake_num) {
    using type = test_class;
    constexpr auto n = 1;
    using allocator_t = custom::allocator<type, n>;

    auto is_deallocate_fail = false;
    try {
        allocator_t allocator;
        auto element = allocator.allocate(n);
        allocator.deallocate(element, n + 1);
    }
    catch (const std::bad_alloc &e) {
        is_deallocate_fail = true;
    }

    EXPECT_TRUE(is_deallocate_fail);
}

TEST(allocator, construct) {
    using type = test_class;
    constexpr auto n = 1;
    using allocator_t = custom::allocator<type, n>;

    try {
        allocator_t allocator;
        auto element = allocator.allocate(n);
        EXPECT_FALSE(element->is_ctor_called());
        allocator.construct(element);
        EXPECT_TRUE(element->is_ctor_called());
    }
    catch (const std::bad_alloc &e) {
        FAIL() << e.what();
    }
}

TEST(allocator, destruct) {
    using type = test_class;
    constexpr auto n = 5;
    constexpr auto value = 123;
    using allocator_t = custom::allocator<type, n>;

    try {
        auto *allocator = new allocator_t;
        auto element = allocator->allocate(n);
        allocator->construct(element);
        EXPECT_FALSE(element->is_dtor_called());
        allocator->destroy(element);
        EXPECT_TRUE(element->is_dtor_called());
    }
    catch (const std::bad_alloc &e) {
        FAIL() << e.what();
    }
}

TEST(container_node, node) {
    using type = test_class;
    using node_t = custom::container<type>::node;

    type element{};
    node_t node{element};
    auto isEq = (node.data == element);

    EXPECT_TRUE(isEq);
    EXPECT_EQ(node.next, nullptr);
}

TEST(container_iterator, operator_plus_plus) {
    using type = int;
    using container_t = custom::container<type>;
    using node_t = container_t::node;
    using iterator_t = container_t::iterator;

    type element1{1}, element2{2};
    node_t node1{element1}, node2{element2};
    node1.next = &node2;
    iterator_t it{&node1};
    EXPECT_EQ(*it, element1);
    EXPECT_EQ(*(++it), element2);
}

TEST(container_iterator, operator_equal_equal) {
    using type = int;
    using container_t = custom::container<type>;
    using node_t = container_t::node;
    using iterator_t = container_t::iterator;

    type element1{1}, element2{2};
    node_t node1{element1}, node2{element2};
    node1.next = &node2;
    iterator_t it1{&node1}, it2{&node2};
    auto isEq = ++it1 == it2;
    EXPECT_TRUE(isEq);
}

TEST(container_iterator, operator_not_equal) {
    using type = int;
    using container_t = custom::container<type>;
    using node_t = container_t::node;
    using iterator_t = container_t::iterator;

    type element1{1}, element2{2};
    node_t node1{element1}, node2{element2};
    node1.next = &node2;
    iterator_t it1{&node1}, it2{&node2};
    auto isNe = it1 != it2;
    EXPECT_TRUE(isNe);
}

TEST(container, push_back) {
    using type = int;
    using container_t = custom::container<type>;
    using iterator_t = container_t::iterator;

    container_t container{};
    type element{123};
    container.push_back(element);
    EXPECT_EQ(*container.begin(), element);
}

TEST(container, begin_end) {
    using type = int;
    using container_t = custom::container<type>;
    using iterator_t = container_t::iterator;

    container_t container{};
    type element1{1}, element2{2};
    container.push_back(element1);
    container.push_back(element2);

    auto i = 0;
    for (const auto &value : container) {
        EXPECT_EQ(value, ++i);
    }
}


int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}