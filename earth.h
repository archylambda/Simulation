#ifndef EARTH_H
#define EARTH_H
#include "model.h"
#include <fstream>
#include <string>
#include <map>
using namespace std;

class TEarth : public TModel
{
private:
    //угловая скорость вращения земли
    const long double Omega = 7.292115e-5; //рад/сек
    //радис земли
    const long double R = 6371.3; // km

    //вывод в файл
    fstream outfile_;

public:

    TEarth();

    virtual void getRight( const TVector& X, long  double t, TVector& Y );

    virtual void addResult(const TVector& X, long double t );

    ~TEarth();
};

#endif // EARTH_H
