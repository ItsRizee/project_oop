#ifndef WEEKEND_PLAN_H
#define WEEKEND_PLAN_H

#include "./PricingStrategy.h"

class SummerPlan : public PricingStrategy {
public:
    double calculate(double price) const override;
};

#endif