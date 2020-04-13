#ifndef CUSTOMMODEL_H
#define CUSTOMMODEL_H
#include "model.h"
#include <string>
#include <fstream>

using namespace std;

class TCustomModel : public TModel
{
protected:
    fstream outfile_;
    string filename_;
public:
    TCustomModel() : TModel(){};
    TCustomModel(const string &filename);
    TCustomModel(const string &filename, const long double &sampIncr, const long double &endTime);

    inline void setSamplingIncrement(const long double &_SamplingIncrement){
        SamplingIncrement = _SamplingIncrement;
    }
    inline void setEndTime(const long double &_t1){
        t1 = _t1;
    }


    virtual void prepareResult() override;
    virtual void addResult(const TVector &X, long double t) override;
    virtual void clearResult() override;



};

#endif // CUSTOMMODEL_H
