#include "Employee.h"

Employee::Employee(char *username, PositionType position) {
    this->username = username;
    this->position = position;
}

char *Employee::GetUsername() const {
    return username;
}

PositionType Employee::GetPosition() const {
    return position;
}

void Employee::SetPosition(PositionType newPosition) {
    position = newPosition;
}
