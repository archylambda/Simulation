#include "sinus.h"
#include <string>
#include <iostream>
#include <math.h>
//поменять
int STATE_SHAPE = 1;
string filename = "result.txt";

Sinus::Sinus()
{
    X0.resize(STATE_SHAPE);
    X0[0] = 1;

    //запись в файл
    outfile_.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
    try{
        outfile_.open(filename, ios::out);
    } catch (fstream::failure e){
        cerr << "Exception opening file\n";
    }
}

void Sinus::getRight(const TVector &X, long double t, TVector &Y){
    Y[0] = sinl(t);
}

void Sinus::addResult(const TVector &X, long double t){

    outfile_ << t << ' ' << X[0] << endl;
}
