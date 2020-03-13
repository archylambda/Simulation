#include "tvector.h"
#include <string>
#include <exception>
#include <sstream>
#include <math.h>

using namespace std;

long double sp_tanl(long double phi){
    if (phi == M_PI/2){
        return INFINITY;
    } else if (phi == -M_PI/2) {
        return -INFINITY;
    } else {
        return tanl(phi);
    }
}
namespace StdLinearAlgebra {
//унарный минус
TVector TVector::operator -() const{
     TVector temp(*this);
     for (size_t i = 0; i < this->size(); i++){
         if(temp[i]!=0)
            temp[i] = -temp[i];
     }
     return temp;
}
//вычитание векторов
TVector TVector::operator -(const TVector& arg) const{
    if(this->size() != arg.size()){
        stringstream ss;
        ss << "Dimension of vectors does not coincide" << endl;
        throw runtime_error(ss.str());

    } else {
        TVector res(this->size());
        for (size_t i = 0; i < this->size(); i++){
            res[i] = (*this)[i] - arg[i];
        }
        return res;
    }
}
//сумма векторов
TVector TVector::operator +(const TVector& arg) const{
    if(this->size() != arg.size()){
        stringstream ss;
        ss << "Dimension of vectors does not coincide" << endl;
        throw runtime_error(ss.str());

    } else {
        TVector res(this->size());
        for (size_t i = 0; i < this->size(); i++){
            res[i] = (*this)[i] + arg[i];
        }
        return res;
    }
}
//умножение вектора на число
TVector TVector::operator *(long double arg) const{

        TVector lvalue(*this);
        for (auto& k: lvalue){
            k *= arg;
        }
        return lvalue;

}
//скалярное умножение векторов
long double TVector::operator *(const TVector& arg) const{
    if(this->size() != arg.size()){
        stringstream ss;
        ss << "Dimension of vectors does not coincide" << endl;
        throw runtime_error(ss.str());

    } else {
        long double res = 0;
        for (size_t i = 0; i < this->size(); i++){
            res += (*this)[i] * arg[i];
        }
        return res;
    }
}
//умножение вектора на матрицу
TVector TVector::operator *(const TMatrix &arg) const{
    if(this->size() != arg.rowCount()){
        stringstream ss;
        ss << "Dimension of vectors does not coincide" << endl;
        throw runtime_error(ss.str());

    } else {
        TVector res(this->size());
        for (size_t i = 0; i < this->size(); i++){
            for(size_t j = 0; j<this->size(); j++){
                res[i] += (*this)[j]*arg(j,i);
            }
        }
        return res;
    }
}
//векторное произведение векторов
TVector TVector::operator ^(const TVector& arg) const{
    if((this->size() != 3) && (arg.size() != 3)){
        stringstream ss;
        ss << "Vectornoe multiple only for state-vectors with size: 3" << endl;
        throw runtime_error(ss.str());

    } else {
        TVector res(3);
        for (size_t i = 0; i < this->size(); i++){
            int i1 = (i + 1) % 3;
            int i2 = (i + 2) % 3;
            res[i] = (*this)[i1] * arg[i2] - (*this)[i2] * arg[i1];
            }

        return res;
    }
}
// умножения числа на вектор
TVector operator* (long double lvalue, const TVector& rvalue){
    TVector res(rvalue.size());
    for (size_t i =0; i < rvalue.size(); i++){
        res[i] = lvalue * rvalue[i];
    }
    return res;

}
//модуль вектора
long double TVector::length() const {
    long double sum = 0;
    for(const auto& k: *this){
        sum += k*k;
    }

    return sqrtl(sum);
}

TVector TVector::GetNorm() const{
    size_t size = this->size();
    long double len = this->length();

    TVector res(*this);
    for (size_t i = 0; i < size; i++){
        res[i] /= len;
    }

    return res;
}

TVector TVector::rotateByRodrigFormula(double phi, const TVector& axis) const{

        TVector res;
        TVector axisN;
        axisN = axis.GetNorm();

        res = (axisN*(*this))*(1 - cosl(phi))*axisN + (axisN^(*this))*sinl(phi) + (*this)*cosl(phi);

        return res;

}

TVector TVector::rotate(double phi, const TVector& axis) const{

    TQuaternion l(phi,axis);
    TQuaternion value(0, (*this)[0], (*this)[1], (*this)[2]);
    TQuaternion rotate;


    rotate = (l * value) * (l.conj());

    return rotate.vect();
}

TVector TVector::rotateByQuaternion(const TQuaternion& L) const{

    TQuaternion value(0, (*this)[0], (*this)[1], (*this)[2]);
    TQuaternion rotate;

    rotate = (L * value) * (!L);

    return rotate.vect();
}
// ---------------TMatrix----------------
void TMatrix::resize(size_t n, size_t m){
    BaseMatrix::resize(n);
    for (size_t i = 0; i < ((*this).rowCount()); i++){
        (*this)(i).resize(m);
    }


}


TMatrix TMatrix::operator - () const{
    TMatrix mat(*this);
    for(size_t i = 0; i < rowCount(); i++)
        for(size_t j = 0; j < colCount();j++)
            mat(i,j) = -mat(i,j);
    return mat;
}

//оператор вычитания матриц
TMatrix TMatrix::operator - (const TMatrix& arg) const{
    if(this->size() != arg.size()){
        stringstream ss;
        ss << "Dimensions of Matrix are not equal" << endl;
        throw runtime_error(ss.str());

    } else {
        TMatrix res(this->rowCount(),this->colCount());
        for (size_t i = 0; i < this->rowCount(); i++){
            for(size_t j = 0; j< this->colCount(); j++){
                res(i,j) = (*this)(i,j) - arg(i,j);
            }
        }
        return res;
    }

}

//оператор сложения матриц
TMatrix TMatrix::operator + (const TMatrix& arg) const{
    if(this->size() != arg.size()){
        stringstream ss;
        ss << "Dimensions of Matrix are not equal" << endl;
        throw runtime_error(ss.str());

    } else {
        TMatrix res(this->rowCount(),this->colCount());
        for (size_t i = 0; i < this->rowCount(); i++){
            for(size_t j = 0; j< this->colCount(); j++){
                res(i,j) = (*this)(i,j) + arg(i,j);
            }
        }
        return res;
    }

}

// Оператор умножения матрицы на число
TMatrix TMatrix::operator * (long double arg) const{
    TMatrix val(*this);
    for (auto& k: val){
        for (auto& n: k){
            n *= arg;
        }
    }
    return val;
}

// Оператор умножения матриц
TMatrix TMatrix::operator * (const TMatrix& arg) const{
    if(this->colCount() != arg.rowCount()){
        stringstream ss;
        ss << "Dimensions of Matrix are not incompatible" << endl;
        throw runtime_error(ss.str());

    } else {
        TMatrix res(this->rowCount(),arg.colCount());
        for (size_t i = 0; i < this->rowCount(); i++){
            for (size_t j = 0; j < arg.colCount(); j++){
                for(size_t k = 0; k < this->colCount(); k++)
                    res(i,j) += (*this)(i,k) * arg(k,j);
            }
        }
        return res;
    }
}

// Оператор умножения матрицы на вектор
TVector TMatrix::operator * (const TVector& arg) const{
    if(this->colCount() != arg.size()){
        stringstream ss;
        ss << "Dimensions of Matrix are not incompatible" << endl;
        throw runtime_error(ss.str());

    } else {

        TVector res(this->rowCount());
        for (size_t i = 0; i < this->rowCount(); i++){
            for(size_t j = 0; j < this->colCount(); j++){
                res[i] += (*this)(i,j)*arg[j];
            }
        }

        return res;
    }
}

// Дружественная функция - оператор умножения числа на матрицу
TMatrix operator * (long double lvalue, const TMatrix& rvalue){
    TMatrix res(rvalue);
    for (auto& k: res){
        for (auto& n: k){
            n *= lvalue;
        }
    }
    return res;
}

// Оператор обращения матриц (метод Гаусса)
TMatrix TMatrix::operator ! () const {
    TMatrix Mat(*this);
    size_t size = Mat.rowCount();
    TMatrix res = TMatrix::E(size);
    for (size_t i = 0; i < size; i++){
        //если ведущий элемент равен 0
        if (Mat(i,i) <= 1.08420217248550443401e-19){
            for (size_t l = i + 1; l < size; l++){
                if (Mat(l,i) != 0){
                    Mat.swapRows(i,l);
                    break;
                } else if (l == size - 1) {
                    stringstream ss;
                    ss << "Matrix is Vyrojdennaya" << endl;
                    throw runtime_error(ss.str());
                }
            }

        }
        //-"-
        long double ForwElem = Mat(i,i);
        for(size_t j = 0;j < size; j++){
            Mat(i,j) /= ForwElem;
            res(i,j) /= ForwElem;

        }
        for(size_t k = 0;k < size;k++){
            if (k==i){continue;}
            long double matki = Mat(k,i);
            for(size_t j = 0; j < size; j++){
                res(k,j) -= matki*res(i,j);
                Mat(k,j) -= matki*Mat(i,j);

            }
        }


    }

    return res;

}



// Функция вычисления детерминанта
long double TMatrix::det() const{
    int swapcount = 0;
    long double res = 1;
    TMatrix Mat(*this);
    size_t size = Mat.rowCount();
    for (size_t i = 0; i < size - 1; i++){
        if (fabsl(Mat(i,i)) <= 1.08420217248550443401e-19){
            for (size_t l = i + 1; l < size; l++){
                if (Mat(l,i) != 0){
                    Mat.swapRows(i,l);
                    swapcount++;
                    break;
                } else if (l == size - 1) {
                    return 0;
                }
            }

        }
        for(size_t k = i + 1;k < size; k++){
            long double mult = Mat(k,i)/Mat(i,i);
            for (size_t j = i; j < size; j++){
                Mat(k,j) -= mult*Mat(i,j);
            }
        }

    }

    for (size_t i = 0; i < size; i++){
        res *= Mat(i,i);
    }

    return (swapcount == 0) ?  res : res *= powl(-1,swapcount);

}

// Функция формирования единичной матрицы
TMatrix TMatrix::E(size_t n){
    TMatrix E(n,n);
    for(size_t i = 0; i < n;i++){
        E(i,i) = 1;
        for(size_t j=i+1; j < n;j++){
            E(i,j) = E(j,i) = 0;
        }
    }

    return E;
}

TMatrix TMatrix::t() const{
    size_t rowCount = this->colCount(),
           colCount = this->rowCount();
    TMatrix res(rowCount, colCount);

    for (size_t i = 0; i < rowCount; i++){
        for(size_t j = 0; j < colCount; j++){
            res(i,j) = (*this)(j,i);
        }
    }
    return res;

}
// Функция перестановки строк
TMatrix& TMatrix::swapRows(size_t i, size_t j){
    TVector i_row((*this)(i));
    TVector j_row((*this)(j));

    (*this)[i] = j_row;
    (*this)[j] = i_row;

    return *this;
}

TMatrix TSymmetricMatrix::getLowerMatrix() const{
    size_t size = (*this).rowCount();
    TSymmetricMatrix res(size);
    for(size_t i = 0; i < size; i++){
        for(size_t j = 0; j <= i; j++){
        long double SumOfNotDiagonally = 0;
            if(i == j){
                for(size_t k = 0; k < i;k++){
                    SumOfNotDiagonally += res(i,k)*res(i,k);
                }
                res(i,i) = sqrt((*this)(i,i) - SumOfNotDiagonally);
                if ((res(i,i) == 0) || ((*this)(i,i) - SumOfNotDiagonally < 0)){
                    stringstream ss;
                    ss << "Positive Definite Matrix" << endl;
                    throw runtime_error(ss.str());
                }

            } else {
                for(size_t k =0; k < j;k++){
                    SumOfNotDiagonally+= res(i,k)*res(j,k);
                }
                res(i,j) = ((*this)(i,j) - SumOfNotDiagonally)/res(j,j);
            }
        }
    }
    return res;
}

TSymmetricMatrix TSymmetricMatrix::operator ! () const {
    TSymmetricMatrix Mat(*this);
    size_t size = Mat.rowCount();
    TSymmetricMatrix res(size);
    TSymmetricMatrix LowerMatrix(size);

    LowerMatrix = getLowerMatrix();


    for(int i = size-1; i >= 0; i--){
        for(int j = i; j >= 0; j--){
            long double SumOfNotDiagonally = 0;
            if (j == i){
                for(size_t k = i+1; k < size; k++){
                    SumOfNotDiagonally += LowerMatrix(k,i)*res(k,i);
                }
                res(i,i)= (1/LowerMatrix(i,i) - SumOfNotDiagonally)/LowerMatrix(i,i);
            } else {
                for(size_t k = j + 1; k < size; k++){
                    SumOfNotDiagonally += LowerMatrix(k,j)*res(k,i);
                }
                res(i,j) = -SumOfNotDiagonally/LowerMatrix(j,j);
                res(j,i) = res(i,j);
            }
        }
    }

    return res;
}

//----------------TQuanterion----------------------
//конструктор по компонентам квартениона
TQuaternion::TQuaternion(long double l0, long double l1, long double l2, long double l3){

    q0 = l0;

    Q.resize(3);

    Q[0] = l1;
    Q[1] = l2;
    Q[2] = l3;
}
//конструктор по углу поворота (рад.) и оси вращения
TQuaternion::TQuaternion(long double phi, const TVector & e){
    TVector Ne(3);
    Ne = e.GetNorm();

    q0 = cosl(phi/2);

    Q.resize(3);

    Q[0] = sinl(phi/2)*Ne[0];
    Q[1] = sinl(phi/2)*Ne[1];
    Q[2] = sinl(phi/2)*Ne[2];
}
//конструктор копирования
TQuaternion::TQuaternion(const TQuaternion &rvalue){

    q0 = rvalue.q0;

    Q.resize(3);

    Q[0] = rvalue.Q[0];
    Q[1] = rvalue.Q[1];
    Q[2] = rvalue.Q[2];
}
//оператор присваивания
TQuaternion& TQuaternion::operator = (const TQuaternion& rvalue){

    q0 = rvalue.q0;

    Q.resize(3);

    Q[0] = rvalue.Q[0];
    Q[1] = rvalue.Q[1];
    Q[2] = rvalue.Q[2];

    return *this;
}

//оператор вычитания кватернионов
TQuaternion TQuaternion::operator - (const TQuaternion& arg) const{
    TQuaternion lvalue(*this);
    TQuaternion res;

    res.q0 = (*this).q0 - arg.q0;

    res.Q = (*this).Q - arg.Q;

    return res;
}

//оператор сложения кватеринионов
TQuaternion TQuaternion::operator + (const TQuaternion& arg) const{
    TQuaternion res;

    res.q0 = (*this).q0 + arg.q0;

    res.Q = (*this).Q + arg.Q;

    return res;
}

// Оператор умножения кватернионов
TQuaternion TQuaternion::operator * (const TQuaternion& arg) const{
    TQuaternion res;

    res.q0 = (*this).q0*arg.q0 - (*this).Q*arg.Q;

    res.Q = (*this).q0*arg.Q + arg.q0*(*this).Q + ((*this).Q^arg.Q);

    return res;

}

TQuaternion TQuaternion::operator * (const TVector& arg) const{
    TQuaternion rvalue(0,arg);
    TQuaternion res;

    res = (*this) * rvalue;

    return res;
}

TQuaternion TQuaternion::operator *(long double arg) const{
    TQuaternion res;

    res.q0 = (*this).q0*arg;
    res.Q = (*this).Q*arg;

    return res;
}

TQuaternion operator * (long double lvalue, const TQuaternion &rvalue){
    TQuaternion res;

    res.q0 = lvalue*rvalue.q0;
    res.Q = lvalue*rvalue.Q;

    return res;
}

TQuaternion TQuaternion::operator ! () const{

    long double sqrmod = powl((*this).mod(),2);
    TQuaternion res;

    res = (*this).conj()*(1./sqrmod);

    return res;

}

TQuaternion TQuaternion::conj() const{
    TQuaternion res(*this);

    res.Q = -res.Q;

    return res;
}

long double TQuaternion::mod() const{
    long double res;

    res = sqrtl(q0*q0 + Q[0]*Q[0] + Q[1]*Q[1] + Q[2]*Q[2]);

    return res;
}

TQuaternion& TQuaternion::norm(){

    (*this) = (*this) * (1./this->mod());

    return *this;
}

TMatrix TQuaternion::toRotateMatrix() const{
    TMatrix res(3,3);
    long double l0 = this->q0,
                l1 = this->Q[0],
                l2 = this->Q[1],
                l3 = this->Q[2];

    res(0,0) = l0*l0 + l1*l1 - l2*l2 - l3*l3; res(0,1) = 2*(l1*l2 - l0*l3); res(0,2) = 2*(l1*l3 + l0*l2);

    res(1,0) = 2*(l1*l2 + l0*l3); res(1,1) = l0*l0 - l1*l1 + l2*l2 - l3*l3; res(1,2) = 2*(l2*l3 - l0*l1);

    res(2,0) = 2*(l1*l3 - l0*l2); res(2,1) = 2*(l2*l3 + l0*l1); res(2,2) = l0*l0 - l1*l1 - l2*l2 + l3*l3;

    return res;
}

TQuaternion TQuaternion::fromKrylovAngles(long double yaw, long double pitch, long double roll){

    TQuaternion res;

    res.q0 = cosl(yaw/2)*cosl(pitch/2)*cosl(roll/2) - sinl(yaw/2)*sinl(pitch/2)*sinl(roll/2);

    res.Q[0] = sinl(yaw/2)*cosl(pitch/2)*cosl(roll/2) + cosl(yaw/2)*sinl(pitch/2)*sinl(roll/2);
    res.Q[1] = cosl(yaw/2)*sinl(pitch/2)*cosl(roll/2) + sinl(yaw/2)*cosl(pitch/2)*sinl(roll/2);
    res.Q[2] = cosl(yaw/2)*cosl(pitch/2)*sinl(roll/2) - sinl(yaw/2)*sinl(pitch/2)*cosl(roll/2);

    return res;

}

}


