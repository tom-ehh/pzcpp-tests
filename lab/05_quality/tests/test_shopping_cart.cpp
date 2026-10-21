// Test suite of ShoppingCart (equivalent to a finished exercise 3).
// It must stay green during the whole exercise.
#include "shopping_cart.h"

#include <stdexcept>

#include <gtest/gtest.h>

class CartTest : public ::testing::Test {
protected:
    void SetUp() override {
        cart.add("apple", 2.50, 4);
        cart.add("bread", 4.20);
        cart.add("cheese", 18.90);
    }

    ShoppingCart cart;
};

TEST_F(CartTest, ItemCountCountsAllUnits) {
    EXPECT_EQ(cart.itemCount(), 6);
}

TEST_F(CartTest, TotalSumsAllProducts) {
    EXPECT_DOUBLE_EQ(cart.total(), 33.10);
}

TEST_F(CartTest, RemoveDeletesProductWithAllUnits) {
    cart.remove("apple");

    EXPECT_EQ(cart.itemCount(), 2);
    EXPECT_DOUBLE_EQ(cart.total(), 23.10);
}

TEST_F(CartTest, AddingSameProductIncreasesQuantity) {
    cart.add("bread", 4.20, 2);

    EXPECT_EQ(cart.itemCount(), 8);
    EXPECT_DOUBLE_EQ(cart.total(), 41.50);
}

TEST(ShoppingCartTest, EmptyCartTotalIsZero) {
    ShoppingCart empty;

    EXPECT_EQ(empty.itemCount(), 0);
    EXPECT_DOUBLE_EQ(empty.total(), 0.0);
}

TEST_F(CartTest, RemovingMissingProductThrows) {
    EXPECT_THROW(cart.remove("milk"), std::out_of_range);
}

TEST_F(CartTest, QuantityMultipliesUnitPrice) {
    cart.add("water", 1.50, 6);

    EXPECT_DOUBLE_EQ(cart.total(), 42.10);
}

TEST_F(CartTest, DiscountReducesTotal) {
    cart.applyDiscount(10);

    EXPECT_DOUBLE_EQ(cart.total(), 29.79);
}

TEST_F(CartTest, ShippingIsChargedBelowThreshold) {
    EXPECT_DOUBLE_EQ(cart.shippingCost(), ShoppingCart::kShippingCost);
}

TEST(ShoppingCartTest, ShippingIsFreeFromThreshold) {
    ShoppingCart cart;
    cart.add("headphones", 100.00);

    EXPECT_DOUBLE_EQ(cart.shippingCost(), 0.0);
}

TEST_F(CartTest, ShippingIsFreeAboveThreshold) {
    cart.add("headphones", 150.00);

    EXPECT_DOUBLE_EQ(cart.shippingCost(), 0.0);
}
