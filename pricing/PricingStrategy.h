#ifndef PRICING_STRATEGY_H
#define PRICING_STRATEGY_H

class PricingStrategy {
public:
    virtual double calculate(double price) const = 0;
    virtual ~PricingStrategy() {}
};

#endif