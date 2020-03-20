#include "moondecorator.h"
#include <math.h>
#include <const.h>
#include <moon.h>

TMoonDecorator::TMoonDecorator(TModel* model):
    TModelDecorator(model)
{
    moon_m_ = new TMoon();

    X0 = getInitialConditions().stack(moon_m_->getInitialConditions());


    
}

TVector TMoonDecorator::gMoon(const TVector &X){
    size_t moon_ind = getOrder() - moon_m_->getOrder();
    long double moon_x = X[moon_ind],
                moon_y = X[moon_ind + 1],
                moon_z = X[moon_ind + 2];

    long double delta_cube = powl(sqrtl((X[0] - moon_x)*(X[0] - moon_x) +
                                        (X[1] - moon_y)*(X[1] - moon_y) +
                                        (X[2] - moon_z)*(X[2] - moon_z)), 3);

    long double r_moon_cube = powl(sqrtl(moon_x*moon_x + moon_y*moon_y + moon_z*moon_z), 3);

    TVector res(getOrder());

    res[3] = MU_MOON*((moon_x - X[0])/delta_cube - moon_x/r_moon_cube);
    res[4] = MU_MOON*((moon_y - X[1])/delta_cube - moon_y/r_moon_cube);
    res[5] = MU_MOON*((moon_z - X[2])/delta_cube - moon_z/r_moon_cube);

    return res;

}

std::vector<TVector> TMoonDecorator::splitX(const TVector &X){
    size_t stackedsize = getOrder(),
            mod_size = getOrder() - moon_m_->getOrder();

    TVector modX(mod_size),
            moonX(mod_size);
    for(size_t i = 0; i < mod_size; i++){
        modX[i] = X[i];
    }

    for(size_t i = mod_size; i < stackedsize; i++){
        moonX[i] = X[i];
    }

    return {modX, moonX};
}

void TMoonDecorator::getRight(const TVector &X, long double t, TVector &Y){
    size_t mod_size = getOrder() - moon_m_->getOrder();


    std::vector<TVector> tupleX = splitX(X);

    TVector modY(mod_size),
            moonY(mod_size);

    TModelDecorator::getRight(tupleX[0], t, modY);
    moon_m_->getRight(tupleX[1], t, moonY);

    Y = modY.stack(moonY) + gMoon(X);

}

TMoonDecorator::~TMoonDecorator(){
    delete moon_m_;
}
