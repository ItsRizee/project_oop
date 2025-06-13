#ifndef PRICING_STRATEGY_H
#define PRICING_STRATEGY_H

class Room;

class PricingStrategy {
public:
    virtual double calculate(const Room* room) const = 0;
    virtual ~PricingStrategy() {}
};

#endif