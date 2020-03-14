#ifndef EARTHSATELLITE_H
#define EARTHSATELLITE_H
#include "model.h"
#include <fstream>

using namespace std;

class TEarthSatellite : public TModel
{
private:
    fstream outfile_;
public:
    TEarthSatellite();

    virtual void getRight(const TVector &X, long double t, TVector &Y);
    virtual void addResult(const TVector &X, long double t);

    ~TEarthSatellite();
};

#endif // EARTHSATELLITE_H
