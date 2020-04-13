#ifndef MOONDECORATOR_H
#define MOONDECORATOR_H

#include "modeldecorator.h"

class TMoonDecorator : public TModelDecorator
{
protected:
    // TModel or TMoon
    TModel* moon_m_;
    TVector gMoon(const TVector &X);

public:
    TMoonDecorator(TModel* model);
    void getRight(const TVector &X, long double t, TVector &Y) override;
    

    inline void setSamplingIncrement(const long double &_SamplingIncrement){
        TModelDecorator::setSamplingIncrement(_SamplingIncrement);
        moon_m_->setSamplingIncrement(_SamplingIncrement);
    }
    inline void setEndTime(const long double &_t1){
        TModelDecorator::setEndTime(_t1);
        moon_m_->setEndTime(_t1);
    }
    ~TMoonDecorator();
};

#endif // MOONDECORATOR_H
