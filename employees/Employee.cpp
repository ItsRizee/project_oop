#include "Employee.h"

Employee::Employee(char *name, PositionType position) {
    this->name = name;
    this->position = position;
}

char *Employee::GetName() const {
    return name;
}

PositionType Employee::GetPosition() const {
    return position;
}