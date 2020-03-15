#include "dateandtime.h"

Date::Date(){
    day = 1;
    month = 1;
    year = 1;
}

Date::Date(int d, int m, int y){
    day = d;
    month = m;
    year = y;

}

Date::Date(int d, int m, int y, Time t){
    Date(d, m, y);
    time = t;
}

long double Date::getUlianDate() const{

    int a = (14 - month)/12;
    int M = month + 12*a - 3;
    int Y = year + 4800 - a;

    int JDN = day + ((153 * M + 2) / 5) + 365 * Y + (Y / 4)
                      - (Y / 100) + (Y / 400) - 32045;

    return JDN + (time.getHour() - 12 / 24.0) + (time.getMin() / 1440.0)
            + (time.getSeconds() / 86400.0);
}

Time::Time(){
    sec = 0;
    min = 0;
    hour = 0;
}
Time::Time(int h, int m, int s){
    int sum_in_seconds = h*3600 + m*60 + s;
    sec = sum_in_seconds % 60;
    min = sum_in_seconds % 3600 / 60;
    hour = sum_in_seconds / 3600;
}

