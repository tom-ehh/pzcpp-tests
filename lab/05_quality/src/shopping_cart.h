#pragma once

#include <string>
#include <vector>

// A shopping cart. Amounts are in złoty, e.g. 19.99.
class ShoppingCart {
public:
    static constexpr double kFreeShippingThreshold = 100.00;
    static constexpr double kShippingCost = 9.99;

    // Adds `quantity` units of a product. Adding a product that is already
    // in the cart increases its quantity (the unit price stays the same).
    // Throws std::invalid_argument if unitPrice < 0 or quantity < 1.
    void add(const std::string& name, double unitPrice, int quantity = 1);

    // Removes a product with all its units.
    // Throws std::out_of_range if the product is not in the cart.
    void remove(const std::string& name);

    // Number of units of all products.
    int itemCount() const;

    // Sum of unitPrice * quantity of all products, after the discount.
    // A discounted total is rounded to whole grosze (half up).
    double total() const;

    // Sets a percentage discount applied to total().
    // Throws std::invalid_argument if percent is outside [0, 100].
    void applyDiscount(int percent);

    // 0 when total() is at least kFreeShippingThreshold, otherwise kShippingCost.
    double shippingCost() const;

private:
    struct Item {
        std::string name;
        double unitPrice;
        int quantity;
    };

    std::vector<Item> items_;
    int discountPercent_ = 0;
};

// Formats an amount for display, e.g. 1234.5 -> "1234,50 zł".
std::string formatPrice(double amount);
