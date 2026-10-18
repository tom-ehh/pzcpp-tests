// Demo for notebook 03: in what order GoogleTest creates, sets up,
// tears down and destroys test fixtures.
#include <iostream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

class LifecycleTest : public ::testing::Test {
protected:
    LifecycleTest() { std::cout << "  constructor\n"; }
    ~LifecycleTest() override { std::cout << "  destructor\n"; }

    static void SetUpTestSuite() { std::cout << "SetUpTestSuite (once, before the first test)\n"; }
    static void TearDownTestSuite() { std::cout << "TearDownTestSuite (once, after the last test)\n"; }

    void SetUp() override {
        std::cout << "  SetUp\n";
        items.push_back("first");
    }
    void TearDown() override { std::cout << "  TearDown\n"; }

    std::vector<std::string> items;
};

TEST_F(LifecycleTest, AddsItem) {
    std::cout << "  body of AddsItem\n";
    items.push_back("second");
    EXPECT_EQ(items.size(), 2u);
}

TEST_F(LifecycleTest, SeesOnlyItsOwnItems) {
    std::cout << "  body of SeesOnlyItsOwnItems\n";
    EXPECT_EQ(items.size(), 1u);  // the item added by AddsItem is gone
}
