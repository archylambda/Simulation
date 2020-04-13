#include "earth.h"
#include "const.h"
#include "math.h"
#include "specmath.h"
#include <iostream>

TVector TEarth::getStartCoords(){
    //на дату 01.01.2019 0:00

    TVector res(6);
    res[0] = (-1)*2.566123740124270e7;
    res[1] = 1.339350231544666e8;
    res[2] = 5.805149372446711e7;
    res[3] = (-1)*2.983549561177192*10;
    res[4] = (-1)*4.846747552523134;
    res[5] = (-1)*2.100585886567924;

    return res;
}

TEarth::TEarth(){
    X0 = getStartCoords();
}

TEarth::TEarth(const string &filename, const long double &sampIncr, const long double &endTime) :
    TCustomModel(filename, sampIncr, endTime)
{

    X0 = getStartCoords();

}

void TEarth::getRight(const TVector &X, long double t, TVector &Y){
    long double len = X.length();

    Y[0] = X[3];
    Y[1] = X[4];
    Y[2] = X[5];
    Y[3] = -MU_S*X[0]/(len*len*len);
    Y[4] = -MU_S*X[1]/(len*len*len);
    Y[5] = -MU_S*X[2]/(len*len*len);


}


