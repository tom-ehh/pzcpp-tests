#include "ticket.h"

namespace {
constexpr int kFullPriceCents = 2000;
}

int ticketPriceCents(int age) {
    if (age < 7) {
        return 0;
    }
    if (age >= 65) {
        return kFullPriceCents / 2;
    }
    return kFullPriceCents;
}
