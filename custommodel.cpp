#include "custommodel.h"
#include <iostream>

TCustomModel::TCustomModel(const string &filename)
{
    filename_ = filename;
}

TCustomModel::TCustomModel(const string &filename, const long double &sampIncr, const long double &endTime){
    filename_ = filename;

    SamplingIncrement = sampIncr;
    t1 = endTime;
}

void TCustomModel::prepareResult(){
    //запись в файл
    outfile_.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
    try{
        outfile_.open(filename_, ios::out);
    } catch (fstream::failure e){
        cerr << "Exception opening file\n";
    }
}

void TCustomModel::addResult(const TVector &X, long double t){

    outfile_ << t << ' ';

    for(int i = 0; i < 3; i++){
        outfile_ << X[i] << ' ';
    }
    outfile_ << endl;

}

void TCustomModel::clearResult(){
    outfile_.close();
}
