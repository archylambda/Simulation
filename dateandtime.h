#ifndef DATEANDTIME_H
#define DATEANDTIME_H
#include <iostream>

using namespace std;

class Time{
public:
    int getHour() const{
        return hour;
    }
    int getMin() const{
        return min;
    }
    int getSeconds() const{
        return sec;
    }

    Time();

    Time(int h, int m, int s);

private:
  int hour;
  int min;
  int sec;
};

class Date {
public:
    int GetYear() const{
        return year;
    }
    int GetMonth() const{
        return month;
    }
    int GetDay() const{
        return day;
    }

    Date();
    Date(int d, int m, int y);
    Date(int d, int m, int y, Time t);

    long double getUlianDate() const;
private:
  int year;
  int month;
  int day;

  Time time;
};

#endif // DATEANDTIME_H
