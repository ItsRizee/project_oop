#include "CustomerStatus.h"

CustomerStatus::CustomerStatus(StatusType type) : type(type) {}

int CustomerStatus::GetDiscount() const {
    switch (type) {
        case StatusType::Basic: return 0;
        case StatusType::Gold: return 10;
        case StatusType::Platinum: return 20;
        default: return 0;
    }
}

StatusType CustomerStatus::GetStatusType() const {
    return type;
}

void CustomerStatus::SetStatusType(StatusType newType) {
    type = newType;
}