#ifndef MOON_H
#define MOON_H
#include "custommodel.h"
#include <fstream>
using namespace std;

class TMoon : public TCustomModel
{
private:
    TVector getStartCoords();
public:
    TMoon();
    TMoon(const string &filename, const long double &sampIncr, const long double &endTime);

    virtual void getRight( const TVector& X, long  double t, TVector& Y ) override;

};

#endif // MOON_H
