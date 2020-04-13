#include "sundecorator.h"
#include <const.h>
#include <math.h>
#include "earth.h"
#include <iostream>

TSunDecorator::TSunDecorator(TModel* model) :
    TModelDecorator(model)
{
    sun_m_ = new TEarth();
    sun_m_->setEndTime(model->getT1());
    sun_m_->setSamplingIncrement(model->getSamplingIncrement());
    X0 = getInitialConditions().stack(sun_m_->getInitialConditions());
}

TVector TSunDecorator::vecToGeliocent(const TVector &X){
    /*если в методе данного декоратора, то последним "застаканным снизу"
    вектором будет вектор положения земли в гелиоцентрической системе координат*/
    size_t earth_ind = getOrder() - sun_m_->getOrder();

    TVector res(X.size());
    // а вектор декорируемого спутника в начале общего вектора модели
    res[0] = X[earth_ind] + X[0];
    res[1] = X[earth_ind + 1] + X[1];
    res[2] = X[earth_ind + 2] + X[2];

    return res;
}

TVector TSunDecorator::gSun(const TVector &X){
    TVector dist_to_sun = vecToGeliocent(X);

    long double delta_cube = powl(sqrtl(dist_to_sun[0]*dist_to_sun[0] +
                                        dist_to_sun[1]*dist_to_sun[1] +
                                        dist_to_sun[2]*dist_to_sun[2]), 3);

    TVector res(getOrder());

    res[3] = MU_S * (-X[0]/delta_cube);
    res[4] = MU_S * (-X[1]/delta_cube);
    res[5] = MU_S * (-X[2]/delta_cube);

    return res;
}


void TSunDecorator::getRight(const TVector &X, long double t, TVector &Y){


    vector<TVector> split_vecs = splitX(X);

    TVector modY(getOrder() - sun_m_->getOrder()),
            sunY(sun_m_->getOrder());

    TModelDecorator::getRight(split_vecs[0], t, modY);
    sun_m_->getRight(split_vecs[1], t, sunY);

    Y = modY.stack(sunY) + gSun(X);
}

TSunDecorator::~TSunDecorator(){
    delete sun_m_;
}
