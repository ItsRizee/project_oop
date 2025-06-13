#ifndef STANDARD_PLAN_H
#define STANDARD_PLAN_H

#include "PricingStrategy.h"

class StandardPlan : public PricingStrategy {
public:
    double calculate(double price) const override;
};

#endif