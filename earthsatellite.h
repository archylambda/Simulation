#ifndef EARTHSATELLITE_H
#define EARTHSATELLITE_H
#include "custommodel.h"
#include "const.h"
#include <fstream>

using namespace std;

class TEarthSatellite : public TCustomModel
{

public:

    TEarthSatellite(const string &filename, const long double &sampIncr,
                    const long double &endTime);
    TEarthSatellite(const string &filename, const long double &sampIncr,
                    const long double &endTime, const TVector &keplerParams);
    virtual void getRight(const TVector &X, long double t, TVector &Y)override;

};

#endif // EARTHSATELLITE_H
