#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include "PositionType.h"

class Employee {
private:
    char* name;
    PositionType position;

public:
    Employee(char* name, PositionType position);

    char* GetName() const;
    PositionType GetPosition() const;
};

#endif