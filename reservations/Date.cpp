#include "Date.h"
#include <iostream>
#include <ctime>

Date::Date() {
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);

    this->day = now->tm_mday;
    this->month = now->tm_mon + 1; // now->tm_mon is from 0 to 11
    this->year = now->tm_year + 1900;// now->tm_year is since 1900
}

Date::Date(int day, int month, int year) : day(day), month(month), year(year) {}

int Date::GetDay() const { return day; }
int Date::GetMonth() const { return month; }
int Date::GetYear() const { return year; }

void Date::SetDate(int day, int month, int year) {
    this->day = day;
    this->month = month;
    this->year = year;
}

bool Date::IsValid() const {
    if (year < 0 || month < 1 || month > 12 || day < 1) return false;

    int maxDay = 31;
    if (month == 2) {
        bool leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
        maxDay = leap ? 29 : 28;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        maxDay = 30;
    }

    return day <= maxDay;
}

int Date::toDays() const {
    int y = year;
    int m = month;
    int days = day;

    if (m < 3) {
        y--;
        m += 12;
    }

    return 365 * y + y / 4 - y / 100 + y / 400 + (153 * m - 457) / 5 + days - 306;
}

int Date::GetNights(const Date& other) const {
    return (*this - other) - 1;
}

bool Date::operator==(const Date& other) const {
    return day == other.day && month == other.month && year == other.year;
}

bool Date::operator!=(const Date& other) const {
    return !(*this == other);
}

bool Date::operator<(const Date& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    return day < other.day;
}

bool Date::operator<=(const Date& other) const {
    return *this < other || *this == other;
}

bool Date::operator>(const Date& other) const {
    return !(*this <= other);
}

bool Date::operator>=(const Date& other) const {
    return !(*this < other);
}

int Date::operator-(const Date& other) const {
    return abs(this->toDays() - other.toDays());
}