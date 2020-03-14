#include "specmath.h"
#include "math.h"
#include "const.h"
SpecMath::SpecMath()
{

}

long double SpecMath::gradToRad(const int &grad, const int &min){
    //0 < min < 60, 0 < grad
    return (grad + min/60.0)*M_PI/180.0;
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

    return 2*M_PI/86400*fmodl(s, 86400); // возвращаю в радианах
}

TVector SpecMath::CartesianToKepler(const TVector &cartesVec){
    TVector R(3);
    R[0] = cartesVec[0]; R[1] = cartesVec[1]; R[0] = cartesVec[2];

    TVector V(3);
    V[3] = cartesVec[3]; V[4] = cartesVec[4]; V[5] = cartesVec[5];

    TVector c = R^V,
            f = (f^c) - MU_EARTH*R*(1./R.length());
    long double p = powl(c.length(),2)/MU_EARTH,
                e = f.length()/MU_EARTH,
                a = p/(1 - e*e);
    TVector e_c = c*(1./c.length()),
            e_f = f*(1./f.length()),
            e_r = R*(1./R.length()),
            e_x(3),
            e_z(3),
            e_Omega(3);
    e_x[0] = 1; e_x[1] = 0; e_x[2] = 0;
    e_z[0] = 0; e_z[1] = 0; e_z[2] = 1;

    e_Omega = (e_z^e_c)*(1./(e_z^e_c).length());
    //??
    long double i = acosl(e_z*e_c),
                Omega = atan2l((e_x^e_Omega) * e_z, e_x * e_Omega),
                w = atan2l((e_Omega^e_f) * e_c, e_Omega * e_f),
                nu = atan2l((e_f^e_r) * e_c, e_f * e_r);

    TVector keplerVec(6);
    keplerVec.push_back(a);
    keplerVec.push_back(e);
    keplerVec.push_back(i);
    keplerVec.push_back(w);
    keplerVec.push_back(Omega);
    keplerVec.push_back(nu);

    return keplerVec;

}
