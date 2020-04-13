#include "moon.h"
#include "const.h"
#include <iostream>

TVector TMoon::getStartCoords(){
    TVector res(6);

    res[0] = -285997.889557;
    res[1] = -250830.089349;
    res[2] = -71384.417342;
    res[3] = 0.643026;
    res[4] = -0.710861;
    res[5] = -0.330661;

    return res;
}

TMoon::TMoon()
{
    //на дату 01.01.2019 0:00

    X0 = getStartCoords();

}

void TMoon::getRight(const TVector &X, long double t, TVector &Y){
    long double len = X.length();

    Y[0] = X[3];
    Y[1] = X[4];
    Y[2] = X[5];
    Y[3] = -MU_EARTH*X[0]/(len*len*len);
    Y[4] = -MU_EARTH*X[1]/(len*len*len);
    Y[5] = -MU_EARTH*X[2]/(len*len*len);
}

