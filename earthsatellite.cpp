#include "earthsatellite.h"
#include <iostream>
#include "specmath.h"

TEarthSatellite::TEarthSatellite(const string &filename, const long double &sampIncr,
                                 const long double &endTime) :
    TCustomModel(filename, sampIncr, endTime)
{
    TVector kepStartCond(6);
    kepStartCond[0] = 42164; kepStartCond[1] = 0; kepStartCond[2] = 0;
    kepStartCond[3] = 0; kepStartCond[4] = 0; kepStartCond[5] = 0;
    X0.resize(6);
    X0 = SpecMath::KeplerToCartesian(kepStartCond);

    filename_ = filename;
}

TEarthSatellite::TEarthSatellite(const string &filename, const long double &sampIncr,
                                 const long double &endTime, const TVector &keplerParams) :
    TCustomModel(filename, sampIncr, endTime)
{
    SamplingIncrement = sampIncr;
    t1 = endTime;

    X0.resize(6);
    X0 = SpecMath::KeplerToCartesian(keplerParams);

    filename_ = filename;
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
