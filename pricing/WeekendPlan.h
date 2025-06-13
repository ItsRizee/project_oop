#ifndef WEEKEND_PLAN_H
#define WEEKEND_PLAN_H

#include "./PricingStrategy.h"

class WeekendPlan : public PricingStrategy {
public:
    double calculate(const Room* room) const;
};

#endif