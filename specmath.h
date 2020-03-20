#ifndef SPECMATH_H
#define SPECMATH_H
#include "tvector.h"

using namespace StdLinearAlgebra;

class SpecMath
{

public:
    SpecMath();

    static long double gradToRad(const int &grad, const int &min);
    //получени матрицы поворота орбитальной СК к инерциальной геоцентрической
    static TMatrix getMatfromOrbToInert(const long double &incl, const long double &longAsc,
                                        const long double &argPer, const long double &trueAnom);
    //перевод из географической СК в Гринвическую СК
    static TVector fromGeographToGrinvich(const long double &R, const long double &h,
                                          const long double &lambda, const long double &phi);
    static TMatrix getMatFromInertToGrinvich(const long double &omega, const long double &t);

    static TMatrix getMatFromInertToTopocentric(const long double &s, const long double &phi);
     //возвращает угол гринвического меридиана на передаваемую юлианскую дату
    static long double getSiderealTime(const long double &JD);

    static TVector KeplerToCartesian(const TVector &keplerVec);
    static TVector CartesianToKepler(const TVector &cartesVec);

};

#endif // SPECMATH_H
