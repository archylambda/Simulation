#ifndef SUNDECORATOR_H
#define SUNDECORATOR_H
#include "modeldecorator.h"

class TSunDecorator : public TModelDecorator
{
protected:
    // TModel or TEarth?
    TModel* sun_m_;
    TVector gSun(const TVector &X);
    TVector vecToGeliocent(const TVector &X);

public:
    TSunDecorator(TModel* model);
    void getRight(const TVector &X, long double t, TVector &Y) override;


    inline void setSamplingIncrement(const long double &_SamplingIncrement){
        TModelDecorator::setSamplingIncrement(_SamplingIncrement);
        sun_m_->setSamplingIncrement(_SamplingIncrement);
    }

    inline void setEndTime(const long double &_t1){
        TModelDecorator::setEndTime(_t1);
        sun_m_->setEndTime(_t1);
    }
    ~TSunDecorator();
};

#endif // SUNDECORATOR_H
