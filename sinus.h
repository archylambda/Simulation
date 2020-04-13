#ifndef SINUS_H
#define SINUS_H
#include "custommodel.h"
#include <fstream>

using namespace std;

class TSinus : public TCustomModel
{

public:
    TSinus(const string &filename, const long double &sampIncr,
           const long double &endTime);
    virtual void getRight(const TVector &X, long double t, TVector &Y) override;

    virtual void addResult(const TVector &X, long double t) override;
};

#endif // SINUS_H
