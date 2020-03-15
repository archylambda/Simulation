//---------------------------------------------------------------------------



#include <math.h>
#include "integrator.h"
#include "model.h"


#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))


using namespace StdLinearAlgebra;
using namespace std;
//===========================================================================
//class TEilerIntegrator
long double TEilerIntegrator::Run(TModel *Model){

    long double //начальное время
                t = Model->getT0(),
                //конечный шаг
                t1 = Model->getT1(),
                // шаг интегрирования
                h = Model->getSamplingIncrement();
    //заполняем вектор состояния системы начальными условиями модели
    TVector X = Model->getInitialConditions();
    //главный цикл
    while (t < t1){
        //получаем правые части
        TVector rp(Model->getOrder());
        Model->getRight(X, t, rp);

        X = X + h*rp;

        Model->addResult(X, t);

        Model->ActionAfterStep(X, t);

        t += h;
    }

}

long double TRungeKuttaIntegrator::Run(TModel *Model){

    long double //начальное время
                t = Model->getT0(),
                //конечный шаг
                t1 = Model->getT1(),
                // шаг интегрирования
                h = Model->getSamplingIncrement();
    //заполняем вектор состояния системы начальными условиями модели
    TVector X = Model->getInitialConditions();
    //инициализируем векторы коэффициентов
    for(int i = 0; i < 4; i++){
        K[i].resize(X.size());
    }

    //главный цикл
    while (t < t1){
        // Вычисляем коэф-ты К
        Model->getRight(X, t, K[0]);
        Model->getRight(X + h/2 * K[0], t + h/2, K[1]);
        Model->getRight(X + h/2 * K[1], t + h/2, K[2]);
        Model->getRight(X + h * K[2], t + h, K[3]);

        X = X + (h/6 * (K[0] + 2*K[1] + 2*K[2] + K[3]));

        Model->addResult(X, t);

        Model->ActionAfterStep(X, t);

        t += h;
    }

}
//===========================================================================
// class TDormandPrinceIntegrator

const long double TDormandPrinceIntegrator::c[7] = { 0, 1./5, 3./10, 4./5, 8./9, 1., 1. };
const long double TDormandPrinceIntegrator::a[7][6] = {
    { 0. },
    { 1./5 },
    { 3./40, 9./40 },
    { 44./45, -56./15, 32./9 },
    { 19372./6561, -25360./2187, 64448./6561, -212./729 },
    { 9017./3168, -355./33, 46732./5247, 49./176, -5103./18656 },
    { 35./384, 0., 500./1113, 125./192, -2187./6784, 11./84 }
};
const long double TDormandPrinceIntegrator::b1[7] = { 35./384, 0., 500./1113, 125./192, -2187./6784, 11./84, 0 };
const long double TDormandPrinceIntegrator::b2[7] = { 5179./57600, 0., 7571./16695, 393./640, -92097./339200, 187./2100, 1./40 };

//---------------------------------------------------------------------------

TDormandPrinceIntegrator::TDormandPrinceIntegrator()
    : TIntegrator()
{
    // Определение машинного нуля
    long double v = 1;
    while (1+v > 1){
        u = v;
        v = v/2;
    }

}

//---------------------------------------------------------------------------

long double TDormandPrinceIntegrator::Run(TModel* Model)
{
     long double // Это время для интегрирования (увеличивается на величину шага интегрирования)
                t = Model->getT0(),
                // Это время для выдачи (увеличивается дискретно на величину плотности)
                t_out = t,
                // Это конечное время
                t1 = Model->getT1(),
                // Это шаг интегрирования
                h,
                // Это шаг после коррекции (инициализируются плотностью выдачи результатов)
                h_new = Model->getSamplingIncrement(),
                // Это ошибка на шаге интегрирования
                e = 0;

    TVector // это вектор состояния на конец шага интегрирования
            X = Model->getInitialConditions(),
            // это вектор состояния на конец шага интегрирования (решение 4-го порядка)
            X1( X.size() ),
            // Это вектор состояния на конец шага для коррекции величины шага (решение 5-го порядка)
            X2( X.size() ),
            // Это вектор для выдачи рез-тов
            Xout ( X.size() ),
            // Это буфер для вычисления коэф-тов К
            Y( X.size() );

    // Подготовка хранилища результатов в модели для повышения эффективности выделения памяти
    Model->prepareResult();

    // Инициализируем размерности коэф-тов K[j]
    for ( int i = 6; i >= 0; --i )
        K[i].resize( X.size() );

    // Счётчик количества сделанных шагов
    int N = 0;

    // Главный цикл
    while ( t < t1 )
    {

        // Устанавливаем шаг на итерацию
        h = h_new;

        // Вычисляем коэф-ты К
        Model->getRight( X, t, K[0] );
        Model->getRight( X + ( K[0]*a[1][0] ) * h, t + c[1]*h, K[1] );
        Model->getRight( X + ( K[0]*a[2][0] + K[1]*a[2][1] ) * h, t + c[2]*h, K[2] );
        Model->getRight( X + ( K[0]*a[3][0] + K[1]*a[3][1] + K[2]*a[3][2] ) * h, t + c[3]*h, K[3] );
        Model->getRight( X + ( K[0]*a[4][0] + K[1]*a[4][1] + K[2]*a[4][2] + K[3]*a[4][3] ) * h, t + c[4]*h, K[4] );
        Model->getRight( X + ( K[0]*a[5][0] + K[1]*a[5][1] + K[2]*a[5][2] + K[3]*a[5][3] + K[4]*a[5][4] ) * h, t + c[5]*h, K[5] );
        Model->getRight( X + ( K[0]*a[6][0] + K[1]*a[6][1] + K[2]*a[6][2] + K[3]*a[6][3] + K[4]*a[6][4] + K[5]*a[6][5] ) * h, t + c[6]*h, K[6] );


//        // Вычисляем решения 4-го и 5-го порядков
//        X1 = X;
//        X2 = X;
//        for (int i = 0; i < 7; i++){
//            X1 = X1 + h*b1[i]*K[i];
//            X2 = X2 + h*b2[i]*K[i];
//        }

//      // Вычисляем значение локальной ошибки

//      e = 0;

//      for (int i = 0; i < X.size();i++){
//          e += pow( h * (X1[i] - X2[i]) / MAX( MAX( fabsl(X[i]), fabsl(X1[i]) ), MAX((long double)1e-5,0.5*u/Eps)), 2);
//      }
//      e = sqrtl( e / X.size() );

        e = 0;
              for ( int k = X.high(); k >= 0; k-- )
              {
              X1[k] = X2[k] = X[k];

                  for ( int j = 0; j < 7; j++ )
                  {
                      X1[k] += K[j][k] * b1[j] * h;
                      X2[k] += K[j][k] * b2[j] * h;
                  }
                e += powl( h * (X1[k] - X2[k]) / MAX( MAX( fabsl(X[k]), fabsl(X1[k]) ), MAX(1e-5, 2*u/Eps) ) , 2 );
              }
              e = sqrtl(e / X.size());

        // вычисляем новое значение шага

        long double den_h = MIN(5., powl(e/Eps,0.2)/0.8);
        long double den = MAX(0.1,den_h);
        h_new = h/den;


        // Если локальная ошибка превышает установленную величину, пытаемся сделать шаг заново
        if ( e > Eps )
            continue;

        // Формирование рез-тов при помощи механизмов плотной выдачи
        while ( (t_out < t + h) && (t_out <= t1) )
        {
            long double theta = (t_out - t)/h,
                        b[6];
            // Расчитываем коэф-ты плотной выдачи
            b[0] = theta*(1 + theta*(-1337./480 + theta*(1039./360 + theta*(-1163./1152))));
            b[1] = 0;
            b[2] = 100*theta*theta*(1054./9275 + theta*(-4682./27825 + theta*(379./5565)))/3;
            b[3] = -5*theta*theta*(27./40 + theta*(-9./5 + theta*(83./96)))/2;
            b[4] = 18225*theta*theta*(-3./250 + theta*(22/375 + theta*(-37./600)))/848;
            b[5] = -22*theta*theta*(-3./10 + theta*(29./30 + theta*(-17./24)))/7;

            // Получаем рез-тат для выдачи
            TVector mult(X.size());
            for (int i = 0; i < 6;i++){
                mult = mult + b[i]*K[i];
            }
            Xout = X + h*mult;
            //выполнение действия после выполненного полного шага
            Model->ActionAfterStep(Xout, t_out);
            // Передача рез-тов в модель
            Model->addResult( Xout, t_out );
            // Наращиваем время выдачи
            t_out += Model->getSamplingIncrement();
        }

        // Обновлем Х решением 5-го порядка и наращиваем время на величину сделанного шага
        X = X1;
        t += h;

        // Считаем количество итераций для вычисления глобальной погрешности
        N++;
    }
}
