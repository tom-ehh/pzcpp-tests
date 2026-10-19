// These tests execute every line and every branch of ticketPriceCents()...
// but do they really check it well?
#include "ticket.h"

#include <gtest/gtest.h>

TEST(TicketTest, ChildTravelsFree) {
    EXPECT_EQ(ticketPriceCents(3), 0);
}

TEST(TicketTest, AdultPaysFullPrice) {
    EXPECT_EQ(ticketPriceCents(30), 2000);
}

TEST(TicketTest, SeniorPaysHalf) {
    EXPECT_EQ(ticketPriceCents(80), 1000);
}
