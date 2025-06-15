#ifndef CUSTOMERSTATUS_H
#define CUSTOMERSTATUS_H

#include "StatusType.h"

class CustomerStatus {
private:
    StatusType type;
public:
    CustomerStatus(StatusType type);

    double GetDiscount() const;
    StatusType GetStatusType() const;
    void SetStatusType(StatusType newType);
};

#endif