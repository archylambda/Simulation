#include "sinus.h"
#include <string>
#include <iostream>
#include <math.h>
#include <const.h>
TSinus::TSinus()
{

    X0.resize(1);
    X0[0] = 0;

    //запись в файл
    outfile_.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
    try{
        outfile_.open(filename, ios::out);
    } catch (fstream::failure e){
        cerr << "Exception opening file\n";
    }
}

void TSinus::getRight(const TVector &X, long double t, TVector &Y){
    Y[0] = sinl(t);
}

void TSinus::addResult(const TVector &X, long double t){

    outfile_ << t << ' ' << X[0] << endl;
}

TSinus::~TSinus(){
    outfile_.close();
}
