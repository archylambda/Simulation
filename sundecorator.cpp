#include "sundecorator.h"
#include <const.h>
#include <math.h>
#include <earth.h>
#include <iostream>

TSunDecorator::TSunDecorator(TModel* model) :
    TModelDecorator(model)
{
    sun_m_ = new TEarth();

    X0 = getInitialConditions().stack(sun_m_->getInitialConditions());
}

TVector TSunDecorator::gSun(const TVector &X){
    size_t earth_ind = getOrder() - sun_m_->getOrder();
    long double earth_x = X[earth_ind],
                earth_y = X[earth_ind + 1],
                earth_z = X[earth_ind + 2];
    long double mod_x_gel = earth_x + X[0],
                mod_y_gel = earth_y + X[1],
                mod_z_gel = earth_z + X[2];

    long double delta_cube = powl(sqrtl(mod_x_gel*mod_x_gel +
                                        mod_y_gel*mod_y_gel +
                                        mod_z_gel*mod_z_gel), 3);

//    long double r_sun_cube = powl(sqrtl(mod_x_gel*mod_x_gel + mod_y_gel*mod_y_gel
//                                        + mod_z_gel*mod_z_gel), 3);

    TVector res(getOrder());

    res[3] = MU_S * (-X[0]/delta_cube);
    res[4] = MU_S * (-X[1]/delta_cube);
    res[5] = MU_S * (-X[2]/delta_cube);

    return res;
}

TVector TSunDecorator::vecToGeliocent(const TVector &X){
    TVector res(X.size());

}

std::vector<TVector> TSunDecorator::splitX(const TVector &X){
    int stackedsize = getOrder(),
            mod_size = getOrder() - sun_m_->getOrder();


    TVector modX(mod_size),
            sunX(sun_m_->getOrder());
    for(int i = 0; i < mod_size; i++){
        modX[i] = X[i];
    }

    for(int i = mod_size; i < stackedsize; i++){
        sunX[i] = X[i];
    }

    std::vector<TVector> res(2);
    res[0] = modX; res[1] = sunX;
    return res;
}

void TSunDecorator::getRight(const TVector &X, long double t, TVector &Y){
    int stackedsize = getOrder(),
            mod_size = getOrder() - sun_m_->getOrder();


    TVector modX(mod_size),
            sunX(sun_m_->getOrder());
    for(int i = 0; i < mod_size; i++){
        modX[i] = X[i];
    }

    for(int i = mod_size; i < stackedsize; i++){
        sunX[i] = X[i];
    }


    TVector modY(mod_size),
            sunY(mod_size);

    TModelDecorator::getRight(modX, t, modY);
    sun_m_->getRight(sunX, t, sunY);

    Y = modY.stack(sunY) + gSun(X);
}

TSunDecorator::~TSunDecorator(){
    delete sun_m_;
}
