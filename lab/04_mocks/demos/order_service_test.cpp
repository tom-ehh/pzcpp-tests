// Demo for notebook 04: a service tested with a gMock mock of its dependency.
#include <stdexcept>
#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

// --- production code -------------------------------------------------------

class PaymentError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class PaymentGateway {
public:
    virtual ~PaymentGateway() = default;
    // Returns false when the payment is declined; throws PaymentError when
    // the gateway cannot be reached.
    virtual bool charge(const std::string& customerId, int amountCents) = 0;
};

enum class OrderResult { Accepted, Declined, InvalidAmount, GatewayDown };

class OrderService {
public:
    explicit OrderService(PaymentGateway& gateway) : gateway_(gateway) {}

    OrderResult placeOrder(const std::string& customerId, int amountCents) {
        if (amountCents <= 0) {
            return OrderResult::InvalidAmount;
        }
        try {
            return gateway_.charge(customerId, amountCents) ? OrderResult::Accepted
                                                             : OrderResult::Declined;
        } catch (const PaymentError&) {
            return OrderResult::GatewayDown;
        }
    }

private:
    PaymentGateway& gateway_;
};

// --- tests -----------------------------------------------------------------

using ::testing::_;
using ::testing::Return;
using ::testing::Throw;

class MockPaymentGateway : public PaymentGateway {
public:
    MOCK_METHOD(bool, charge, (const std::string& customerId, int amountCents), (override));
};

TEST(OrderServiceTest, AcceptedWhenPaymentSucceeds) {
    MockPaymentGateway gateway;
    ON_CALL(gateway, charge).WillByDefault(Return(true));  // stub: canned answer
    OrderService service(gateway);

    EXPECT_EQ(service.placeOrder("alice", 1500), OrderResult::Accepted);
}

TEST(OrderServiceTest, ChargesCustomerExactlyOnceWithOrderAmount) {
    MockPaymentGateway gateway;
    EXPECT_CALL(gateway, charge("alice", 1500))  // mock: the call itself is verified
        .Times(1)
        .WillOnce(Return(true));
    OrderService service(gateway);

    service.placeOrder("alice", 1500);
}

TEST(OrderServiceTest, DoesNotChargeInvalidAmount) {
    MockPaymentGateway gateway;
    EXPECT_CALL(gateway, charge(_, _)).Times(0);
    OrderService service(gateway);

    EXPECT_EQ(service.placeOrder("alice", 0), OrderResult::InvalidAmount);
}

TEST(OrderServiceTest, ReportsGatewayDownWhenGatewayThrows) {
    MockPaymentGateway gateway;
    EXPECT_CALL(gateway, charge).WillOnce(Throw(PaymentError("timeout")));
    OrderService service(gateway);

    EXPECT_EQ(service.placeOrder("alice", 1500), OrderResult::GatewayDown);
}
