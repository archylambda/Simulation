#ifndef SUNDECORATOR_H
#define SUNDECORATOR_H
#include <modeldecorator.h>

class TSunDecorator : public TModelDecorator
{
protected:
    // TModel or TEarth?
    TModel* sun_m_;
    TVector gSun(const TVector &X);
    TVector vecToGeliocent(const TVector &X);

    std::vector<TVector> splitX(const TVector &X) override;

public:
    TSunDecorator(TModel* model);
    void getRight(const TVector &X, long double t, TVector &Y) override;

    ~TSunDecorator();
};

#endif // SUNDECORATOR_H
