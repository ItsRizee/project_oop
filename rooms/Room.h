#ifndef ROOM_H
#define ROOM_H

class Room {
public:
    enum class Status {
        Available,
        Occupied,
        UnderRenovation
    };

protected:
    Status status;

public:
    virtual double pricing();
    Status getStatus() const { return status; }
    void setStatus(Status newStatus) { status = newStatus; }
};

#endif