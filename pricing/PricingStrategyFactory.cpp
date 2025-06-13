#include "PricingStrategyFactory.h"

PricingStrategy* PricingStrategyFactory::createPricingStrategy(Date* startDate, Date* endDate) {
    Date firstDaySummer(1,6,2025);
    Date lastDaySummer(30, 9, 2025);

    if (*startDate < firstDaySummer && *endDate < firstDaySummer) {
        return new StandardPlan();
    }

    if (*startDate > lastDaySummer && *endDate > lastDaySummer) {
        return new StandardPlan();
    }

    if (*startDate >= firstDaySummer && *startDate < lastDaySummer && *endDate > firstDaySummer && *endDate <= lastDaySummer) {
        return new SummerPlan();
    }

    if (*startDate < firstDaySummer) {
        if (startDate->GetNights(firstDaySummer) > endDate->GetNights(firstDaySummer)) {
            return new StandardPlan();
        }
        else {
            return new SummerPlan();
        }
    }

    if (*startDate >= firstDaySummer && *startDate < lastDaySummer) {
        if (startDate->GetNights(firstDaySummer) > endDate->GetNights(firstDaySummer)) {
            return new SummerPlan();
        }
        else {
            return new StandardPlan();
        }
    }

    return nullptr;
}