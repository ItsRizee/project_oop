#ifndef STANDARD_PLAN_H
#define STANDARD_PLAN_H

#include "PricingStrategy.h"

class StandardPlan : public PricingStrategy {
public:
    double calculate(const Room* room) const;
};

#endif