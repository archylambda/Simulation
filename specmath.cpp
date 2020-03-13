#include "specmath.h"
#include "math.h"
#include "const.h"
SpecMath::SpecMath()
{

}

long double SpecMath::gradToRad(const int &grad, const int &min){
    //0 < min < 60, 0 < grad
    return (grad + min/60.0)*M_PIl/180.0;
}

TMatrix SpecMath::getMatfromOrbToInert(const long double &incl,  const long double &longAsc,
                                       const long double &argPer,const long double &trueAnomal){
    long double latArg = argPer + trueAnomal;

    TMatrix A(3,3);
    A(0,0) = cosl(latArg)*cosl(longAsc) - sinl(latArg)*sinl(longAsc)*cosl(incl);
        A(0,1) = -sinl(latArg)*cosl(longAsc) - cosl(latArg)*sinl(longAsc)*cosl(incl);
            A(0,2) = sinl(incl)*sinl(longAsc);

    A(1,0) = cosl(latArg)*sinl(longAsc) + sinl(latArg)*cosl(longAsc)*cosl(incl);
        A(1,1) = -sinl(latArg)*sin(longAsc) + cosl(latArg)*cosl(longAsc)*cosl(incl);
            A(1,2) = -sinl(incl)*cosl(longAsc);

    A(2,0) = sinl(latArg)*sin(incl);
        A(2,1) = cosl(latArg)*sinl(incl);
            A(2,2) = cosl(incl);

    return A;
}

TVector SpecMath::fromGeographToGrinvich(const long double &R, const long double &h,
                                         const long double &lambda, const long double &phi){
    TVector X(3);
    X[0] = (R + h)*cosl(phi)*cosl(lambda);
    X[1] = (R + h)*cosl(phi)*sinl(lambda);
    X[2] = (R + h)*sinl(phi);

    return X;
}

TMatrix SpecMath::getMatFromInertToGrinvich(const long double &omega, const long double &t){
    TMatrix A(3,3);
    long double mult = omega*t;

    A(0,0) = cosl(mult);  A(0,1) = sinl(mult);  A(0,2) = 0;
    A(1,0) = -sinl(mult); A(1,1) = cosl(mult); A(1,2) = 0;
    A(2,0) = 0; A(2,1) = 0; A(2,2) = 1;

    return A;
}

TMatrix SpecMath::getMatFromInertToTopocentric(const long double &s, const long double &phi){
    TMatrix A(3,3);

    A(0,0) = -sinl(phi)*cosl(s);  A(0,1) = -sinl(phi)*sinl(s);  A(0,2) = cosl(phi);
    A(1,0) = cosl(phi)*cosl(s); A(1,1) = cosl(phi)*sinl(s); A(1,2) = sinl(phi);
    A(2,0) = -sinl(s); A(2,1) = cosl(s); A(2,2) = 0;

    return A;
}

long double SpecMath::getSiderealTime(const long double &JD){

    int days = int(JD - J2000);
    long double t = days / 36525.0;

    long double s = 24110.54841 + 8640184.812866*t + 0.093104*(t*t) - 0.0000062*(t*t*t);

    return 2*M_PIl/86400*fmodl(s, 86400); // возвращаю в радианах
}
