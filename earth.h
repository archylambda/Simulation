#ifndef EARTH_H
#define EARTH_H
#include "custommodel.h"
#include <fstream>
#include <string>
#include <map>
using namespace std;

class TEarth : public TCustomModel
{
private:
    //угловая скорость вращения земли
    const long double Omega = 7.292115e-5; //рад/сек
    //радис земли
    const long double R = 6371.3; // km

    TVector getStartCoords();
public:
    TEarth();
    TEarth(const string &filename, const long double &sampIncr, const long double &endTime);

    virtual void getRight( const TVector& X, long  double t, TVector& Y ) override;



};

#endif // EARTH_H
