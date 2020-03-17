#include "earthsatellite.h"
#include "const.h"
#include <iostream>
#include <specmath.h>

TEarthSatellite::TEarthSatellite()
{
    TVector kepStartCond(6);
    kepStartCond[0] = 42164; kepStartCond[1] = 0; kepStartCond[2] = 0;
    kepStartCond[3] = 0; kepStartCond[4] = 0; kepStartCond[5] = 0;
    X0.resize(6);
    X0 = SpecMath::KeplerToCartesian(kepStartCond);
    t1 = 20000;
    //запись в файл
    outfile_.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
    try{
        outfile_.open(filename, ios::out);
    } catch (fstream::failure e){
        cerr << "Exception opening file\n";
    }
}

void TEarthSatellite::getRight(const TVector &X, long double t, TVector &Y){
    long double len = X.length();

    Y[0] = X[3];
    Y[1] = X[4];
    Y[2] = X[5];
    Y[3] = -MU_EARTH*X[0]/(len*len*len);
    Y[4] = -MU_EARTH*X[1]/(len*len*len);
    Y[5] = -MU_EARTH*X[2]/(len*len*len);

}

void TEarthSatellite::addResult(const TVector &X, long double t){

    for(int i = 0; i < 3; i++){
        outfile_ << X[i] << ' ';
    }
    outfile_ << endl;

}

TEarthSatellite::~TEarthSatellite(){
    outfile_.close();
}
