#ifndef MOONDECORATOR_H
#define MOONDECORATOR_H

#include "modeldecorator.h"

class TMoonDecorator : public TModelDecorator
{
protected:
    // TModel or TMoon
    TModel* moon_m_;
    TVector gMoon(const TVector &X);

    std::vector<TVector> splitX(const TVector &X) override;

public:
    TMoonDecorator(TModel* model);
    void getRight(const TVector &X, long double t, TVector &Y) override;
    
    ~TMoonDecorator();
};

#endif // MOONDECORATOR_H
