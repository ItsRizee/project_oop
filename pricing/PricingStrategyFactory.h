#ifndef PRICINGSTRATEGYFACTORY_H
#define PRICINGSTRATEGYFACTORY_H

#include "../reservations/Date.h"
#include "./StandartPlan.h"
#include "./SummerPlan.h"

class PricingStrategyFactory {
public:
    static PricingStrategy* createPricingStrategy(Date* startDate, Date* endDate);
};

#endif //PRICINGSTRATEGYFACTORY_H
