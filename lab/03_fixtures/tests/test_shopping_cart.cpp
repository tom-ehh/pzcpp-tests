// Exercise 3: these tests work, but every one of them repeats the same set-up.
// Move the shared set-up into a fixture and add the missing tests (see the notebook).
#include "shopping_cart.h"

#include <stdexcept>

#include <gtest/gtest.h>

TEST(ShoppingCartTest, ItemCountCountsAllUnits) {
    ShoppingCart cart;
    cart.add("apple", 2.50, 4);
    cart.add("bread", 4.20);
    cart.add("cheese", 18.90);

    EXPECT_EQ(cart.itemCount(), 6);
}

TEST(ShoppingCartTest, TotalSumsAllProducts) {
    ShoppingCart cart;
    cart.add("apple", 2.50, 4);
    cart.add("bread", 4.20);
    cart.add("cheese", 18.90);

    EXPECT_DOUBLE_EQ(cart.total(), 33.10);
}

TEST(ShoppingCartTest, RemoveDeletesProductWithAllUnits) {
    ShoppingCart cart;
    cart.add("apple", 2.50, 4);
    cart.add("bread", 4.20);
    cart.add("cheese", 18.90);

    cart.remove("apple");

    EXPECT_EQ(cart.itemCount(), 2);
    EXPECT_DOUBLE_EQ(cart.total(), 23.10);
}

TEST(ShoppingCartTest, AddingSameProductIncreasesQuantity) {
    ShoppingCart cart;
    cart.add("apple", 2.50, 4);
    cart.add("bread", 4.20);
    cart.add("cheese", 18.90);

    cart.add("bread", 4.20, 2);

    EXPECT_EQ(cart.itemCount(), 8);
    EXPECT_DOUBLE_EQ(cart.total(), 41.50);
}
