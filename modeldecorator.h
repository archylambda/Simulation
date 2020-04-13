#ifndef MODELDECORATOR_H
#define MODELDECORATOR_H
#include "custommodel.h"
#include <tuple>
class TModelDecorator : public TCustomModel
{
private:
    TModel* model_;

protected:
    std::vector<TVector> splitX(const TVector &X, size_t _wrapper_X_size = 6);

public:
    TModelDecorator(TModel* model);
    


    void addResult(const TVector &X, long double t) override
    { this->model_->addResult(X, t);};
    void getRight(const TVector &X, long double t, TVector &Y) override {
        this->model_->getRight(X, t, Y);
    }
    void clearResult() override {
        this->model_->clearResult();
    };
    void prepareResult() override {
        this->model_->prepareResult();
    };
    void ActionAfterStep(const TVector &X, long double t) override{
        this->model_->ActionAfterStep(X, t);
    };

    inline void setSamplingIncrement(const long double &_SamplingIncrement){
        TCustomModel::setSamplingIncrement(_SamplingIncrement);
        model_->setSamplingIncrement(_SamplingIncrement);
    };
    inline void setEndTime(const long double &_t1){
        TCustomModel::setEndTime(_t1);
        model_->setEndTime(_t1);
    };
    void setModel(TModel* model) { model_ = model;}

    ~TModelDecorator();
};

#endif // MODELDECORATOR_H
