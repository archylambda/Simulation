#include "sinus.h"
#include <string>
#include <iostream>
#include <math.h>
#include "const.h"
TSinus::TSinus(const string &filename, const long double &sampIncr,
               const long double &endTime):
    TCustomModel(filename, sampIncr, endTime)
{

    X0.resize(1);
    X0[0] = 0;

}

void TSinus::getRight(const TVector &X, long double t, TVector &Y){
    Y[0] = sinl(t);
}

void TSinus::addResult(const TVector &X, long double t){
    outfile_ << t << ' ' << X[0] << endl;
}
