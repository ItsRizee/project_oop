#include "SummerPlan.h"

double SummerPlan::calculate(double price) const {
    return price + (price * 20 / 100); // 20% more
}