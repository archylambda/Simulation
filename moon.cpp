#include "moon.h"
#include "const.h"
#include <iostream>

TMoon::TMoon()
{
    //на дату 01.01.2019 0:00

    X0.resize(6);
    X0[0] = -285997.889557;
    X0[1] = -250830.089349;
    X0[2] = -71384.417342;
    X0[3] = 0.643026;
    X0[4] = -0.710861;
    X0[5] = -0.330661;

    SamplingIncrement = 10;
    t1 = 1000000;

    outfile_.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
    try{
        outfile_.open(filename, ios::out);
    } catch (fstream::failure e){
        cerr << "Exception opening file\n";
    }
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

void TMoon::addResult(const TVector &X, long double t){
    for(int i = 0; i < 6; i++){
        outfile_ << X[i] << ' ';
    }
    outfile_ << endl;
}

TMoon::~TMoon(){
    outfile_.close();
}
