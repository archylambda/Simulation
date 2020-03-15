//#include "earth.h"
//#include "const.h"
//#include "math.h"
//#include "specmath.h"
//#include "dateandtime.h"
//#include <iostream>

//TEarth::TEarth()
//{


//    //получаем угол место гринвического меридиана
//    InitSG_ = SpecMath::getSiderealTime(startDate.getUlianDate());



//    //на дату 01.01.2019 0:00

//    X0.resize(6);
//    X0[0] = (-1)*2.566123740124270e7;
//    X0[1] = 1.339350231544666e8;
//    X0[2] = 5.805149372446711e7;
//    X0[3] = (-1)*2.983549561177192*10;
//    X0[4] = (-1)*4.846747552523134;
//    X0[5] = (-1)*2.100585886567924;
//    //запись в файл
//    outfile_.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
//    try{
//        outfile_.open(outFileName, ios::out);
//    } catch (fstream::failure e){
//        cerr << "Exception opening file\n";
//    }
//}

//void TEarth::jumpModeOn(const Date &reqDate){
//    //режим "прыжка"
//    workMode_ = 1;
//    //выставляем время выдачи результата равным времени интегрирования
//    SamplingIncrement = (reqDate.getUlianDate() - startDate.getUlianDate())*24*3600;
//    t1 = SamplingIncrement;


//}

//void TEarth::simModeOn(const Date& reqDate, long double simDuration, const TVector &initX){
//    //режим моделирования
//    workMode_ = 2;

//    //рассчитываем звёздное время
//    InitSG_ = SpecMath::getSiderealTime(reqDate.getUlianDate());
//    //1 мин
//    SamplingIncrement = 60;

//    t1 = simDuration;
//    //задаём эфемерды Земли (полученные в режиме "прыжка")
//    X0 = initX;

//    clearResult();
//}

//void TEarth::timeAnalysisModeOn(){
//    workMode_ = 3;
//    //время интегрирования - 1 год
//    t1 = 365*24*3600;
//    //выдача результатов каждую минуту
//    SamplingIncrement = 60;

//}
//void TEarth::getRight(const TVector &X, long double t, TVector &Y){
//    long double len = X.length();

//    Y[0] = X[3];
//    Y[1] = X[4];
//    Y[2] = X[5];
//    Y[3] = -MU_S*X[0]/(len*len*len);
//    Y[4] = -MU_S*X[1]/(len*len*len);
//    Y[5] = -MU_S*X[2]/(len*len*len);


//}

//void TEarth::addResult(const TVector &X, long double t){


//    switch (workMode_) {
//    // в режиме прыжка получаем конечные эфемериды
//    case 1:
//        curX_ = X;
//        break;
//    }

//}

//void TEarth::ActionAfterStep(const TVector &X, long double t){

//    //расчёт текущего звёздного времени места
//    earthRotate(t);
//    //обновление вектора тени
//    gnomon_->updateShadow(X, R);

//}

//void TEarth::earthRotate(long double t){

//    SG_ = InitSG_ + Omega*t;
//    gnomon_->setS(SG_);

//}


//TEarth::~TEarth(){

//    delete gnomon_;
//    gnomon_ = nullptr;
//}

