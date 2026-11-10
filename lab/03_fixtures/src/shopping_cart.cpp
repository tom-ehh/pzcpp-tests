#include "shopping_cart.h"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <stdexcept>

void ShoppingCart::add(const std::string& name, double unitPrice, int quantity) {
    if (unitPrice < 0) {
        throw std::invalid_argument("unit price must not be negative");
    }
    if (quantity < 1) {
        throw std::invalid_argument("quantity must be at least 1");
    }
    auto it = std::find_if(items_.begin(), items_.end(),
                           [&name](const Item& item) { return item.name == name; });
    if (it != items_.end()) {
        it->quantity += quantity;
    } else {
        items_.push_back({name, unitPrice, quantity});
    }
}

void ShoppingCart::remove(const std::string& name) {
    auto it = std::find_if(items_.begin(), items_.end(),
                           [&name](const Item& item) { return item.name == name; });
    if (it == items_.end()) {
        throw std::out_of_range("product not in cart: " + name);
    }
    items_.erase(it);
}

int ShoppingCart::itemCount() const {
    int count = 0;
    for (const Item& item : items_) {
        count += item.quantity;
    }
    return count;
}

double ShoppingCart::total() const {
    double sum = 0.0;
    for (const Item& item : items_) {
        sum += item.unitPrice * item.quantity;
    }
    if (discountPercent_ == 0) {
        return sum;
    }
    const double discounted = sum * (100 - discountPercent_) / 100;
    return std::round(discounted * 100) / 100;
}

void ShoppingCart::applyDiscount(int percent) {
    if (percent < 0 || percent > 100) {
        throw std::invalid_argument("discount must be between 0 and 100 percent");
    }
    discountPercent_ = percent;
}

double ShoppingCart::shippingCost() const {
    return total() >= kFreeShippingThreshold ? 0.0 : kShippingCost;
}

std::string formatPrice(double amount) {
    const auto grosze = static_cast<long long>(amount * 100);
    std::ostringstream out;
    out << grosze / 100 << ',' << std::setw(2) << std::setfill('0') << grosze % 100 << " zł";
    return out.str();
}
