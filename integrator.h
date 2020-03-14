//---------------------------------------------------------------------------

#ifndef integratorH
#define integratorH

//подключение заголовочного файла библиотеки векторных и матричных операций
#include "tvector.h"

using namespace StdLinearAlgebra;
// опережающие декларации
class TModel;

class TIntegrator
{
    protected:
        // макисмальная погрешность на шаге
        long double Eps;

    public:
        // базовый конструктор
        TIntegrator() : Eps( 1e-8 ) {}
        inline void setPrecision( long double Eps ) { this->Eps = Eps; }
        inline long double getPrecision() const { return Eps; }
        /* абстрактный метод, реализующий процедуру численного интегрирования вовзращающий глобальную
        погрешность вычислений */
        virtual long double Run(TModel* Model) = 0;
        virtual ~TIntegrator(){}
};

class TEilerIntegrator : public TIntegrator
{
   public:
        TEilerIntegrator(){}
        virtual long double Run(TModel *Model);
        ~TEilerIntegrator(){}
};

class TRungeKuttaIntegrator : public TIntegrator
{
    private:
        TVector K[4];
    public:
        TRungeKuttaIntegrator(){}
        virtual long double Run(TModel *Model);\
        ~TRungeKuttaIntegrator(){}

};

class TDormandPrinceIntegrator : public TIntegrator
{
    private:
        // Коэффициенты a,b,c
        static const long double c[7], a[7][6], b1[7], b2[7];
        // Коэффициенты K[i]
        TVector K[7];
        // Машинный нуль
        long double u;
    public:
        TDormandPrinceIntegrator();
        virtual long double Run(TModel* Model);
        ~TDormandPrinceIntegrator(){}
};


#endif
