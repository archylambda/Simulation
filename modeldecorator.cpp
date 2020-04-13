#include "modeldecorator.h"

TModelDecorator::TModelDecorator(TModel* model)
{
    model_ = model;

    X0.resize(model_->getOrder());
    X0 = model_->getInitialConditions();

    SamplingIncrement = model_->getSamplingIncrement();
    t0 = model_->getT0();
    t1 = model_->getT1();
}

std::vector<TVector> TModelDecorator::splitX(const TVector &X, size_t _wrapper_X_size){

    int stackedsize = getOrder(),
            mod_size = getOrder() - _wrapper_X_size;


    TVector modX(mod_size),
            wrapperX(_wrapper_X_size);
    for(int i = 0; i < mod_size; i++){
        modX[i] = X[i];
    }

    for(int i = mod_size; i < stackedsize; i++){
        wrapperX[i - mod_size] = X[i];
    }

    std::vector<TVector> res(2);
    res[0] = modX; res[1] = wrapperX;
    return res;

}

TModelDecorator::~TModelDecorator(){
    delete model_;
}
