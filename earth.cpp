#include "earth.h"
#include "const.h"
#include "math.h"
#include "specmath.h"
#include <iostream>

TEarth::TEarth()
{

    //на дату 01.01.2019 0:00

    X0.resize(6);
    X0[0] = (-1)*2.566123740124270e7;
    X0[1] = 1.339350231544666e8;
    X0[2] = 5.805149372446711e7;
    X0[3] = (-1)*2.983549561177192*10;
    X0[4] = (-1)*4.846747552523134;
    X0[5] = (-1)*2.100585886567924;

    SamplingIncrement = 10;
    t1 = 10000000;
    //запись в файл

    outfile_.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
    try{
        outfile_.open(filename, ios::out);
    } catch (fstream::failure e){
        cerr << "Exception opening file\n";
    }
}

void TEarth::getRight(const TVector &X, long double t, TVector &Y){
    long double len = X.length();

    Y[0] = X[3];
    Y[1] = X[4];
    Y[2] = X[5];
    Y[3] = -MU_S*X[0]/(len*len*len);
    Y[4] = -MU_S*X[1]/(len*len*len);
    Y[5] = -MU_S*X[2]/(len*len*len);


}

void TEarth::addResult(const TVector &X, long double t){

    for(int i = 0; i < 3; i++){
        outfile_ << X[i] << ' ';
    }
    outfile_ << endl;

}





TEarth::~TEarth(){
    outfile_.close();
}

