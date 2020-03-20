#include "modeldecorator.h"

TModelDecorator::TModelDecorator(TModel* model) :
    model_(model)
{
    X0.resize(model_->getOrder());
    X0 = model_->getInitialConditions();

    SamplingIncrement = model_->getSamplingIncrement();
    t0 = model_->getT0();
    t1 = model_->getT1();
}


TModelDecorator::~TModelDecorator(){
    delete model_;
}
