#ifndef DATE_H
#define DATE_H

class Date {
private:
    int day;
    int month;
    int year;

    int toDays() const;

public:
    Date();
    Date(int day, int month, int year);

    int GetDay() const;
    int GetMonth() const;
    int GetYear() const;
    void SetDate(int day, int month, int year);
    bool IsValid() const;
    int GetNights(const Date& other) const;
    void Print() const;

    bool operator==(const Date& other) const;
    bool operator!=(const Date& other) const;
    bool operator<(const Date& other) const;
    bool operator<=(const Date& other) const;
    bool operator>(const Date& other) const;
    bool operator>=(const Date& other) const;
    int operator-(const Date& other) const;
};

#endif