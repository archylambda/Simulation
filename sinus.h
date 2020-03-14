#ifndef SINUS_H
#define SINUS_H
#include "model.h"
#include <fstream>

using namespace std;

class TSinus : public TModel
{
private:
    fstream outfile_;
public:
    TSinus();

    virtual void getRight(const TVector &X, long double t, TVector &Y) override;

    virtual void addResult(const TVector &X, long double t) override;

    ~TSinus();
};

#endif // SINUS_H
