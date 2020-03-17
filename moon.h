#ifndef MOON_H
#define MOON_H
#include "model.h"
#include <fstream>
using namespace std;

class TMoon : public TModel
{
public:
    TMoon();

    virtual void getRight( const TVector& X, long  double t, TVector& Y );

    virtual void addResult(const TVector& X, long double t );

    fstream outfile_;

    ~TMoon();
};

#endif // MOON_H
