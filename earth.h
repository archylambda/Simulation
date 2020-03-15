//#ifndef EARTH_H
//#define EARTH_H
//#include "model.h"
//#include "dateandtime.h"
//#include <fstream>
//#include <string>
//#include <map>
//using namespace std;

//class TEarth : public TModel
//{
//private:
//    //вектор состояния Земли
//    TVector curX_;
//    //угловая скорость вращения земли
//    const long double Omega = 7.292115e-5; //рад/сек
//    //радис земли
//    const long double R = 6371.3; // km
//    //начальная дата
//    const Date startDate{1,1,2019};
//    //реальная дата и время
//    Date date_;
//    // звёздное время на нчало моделирования
//    long double InitSG_;
//    //звёздное время текущее
//    long double SG_;

//    //вывод в файл
//    fstream outfile_;

//    // режим работы модели
//    // 1 - "прыжок"
//    int workMode_;

//    //моделирование вращения земли
//    void earthRotate(long double t);

//public:

//    TEarth();

//    virtual void getRight( const TVector& X, long  double t, TVector& Y );

//    virtual void addResult(const TVector& X, long double t );

//    virtual void ActionAfterStep(const TVector& X, long double t);

//    void jumpModeOn(const Date& reqDate);
//    void simModeOn(const Date& reqDate, long double simDuration, const TVector &initX);
//    void timeAnalysisModeOn();


//    ~TEarth();
//};

//#endif // EARTH_H
