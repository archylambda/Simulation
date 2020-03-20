#ifndef MODELDECORATOR_H
#define MODELDECORATOR_H
#include <model.h>

class TModelDecorator : public TModel
{
private:
    TModel* model_;

protected:
    virtual std::vector<TVector> splitX(const TVector &X) = 0;

public:
    TModelDecorator(TModel* model);
    
    void addResult(const TVector &X, long double t) override {};
    void getRight(const TVector &X, long double t, TVector &Y) override{
        this->model_->getRight(X, t, Y);
    }
    
    void setModel(TModel* model) { model_ = model;}
    
    ~TModelDecorator();
};

#endif // MODELDECORATOR_H
