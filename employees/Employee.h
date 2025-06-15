#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include "PositionType.h"

class Employee {
private:
    char* username;
    PositionType position;

public:
    Employee(char* username, PositionType position);

    char* GetUsername() const;
    PositionType GetPosition() const;
    void SetPosition(PositionType newPosition);
};

#endif