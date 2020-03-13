#ifndef TVECTOR_H
#define TVECTOR_H
#include <vector>

namespace StdLinearAlgebra {


typedef std::vector<long double> BaseVector;
typedef std::vector<BaseVector> BaseMatrix;

class TMatrix;
class TQuaternion;

class TVector : public BaseVector
{
public:
    TVector() : BaseVector(){}
    TVector(size_t n) : BaseVector(n){}
    //конструктор копий
    TVector(const TVector& rvalue): BaseVector(rvalue){}
    inline size_t high() const { return size() - 1;}
    //унарный минус
    TVector operator -() const;
    //вычитание векторов
    TVector operator -(const TVector& arg) const;
    //сумма векторов
    TVector operator +(const TVector& arg) const;
    //умножение вектора на число
    TVector operator *(long double arg) const;
    //скалярное умножение векторов
    long double operator *(const TVector& arg) const;
    //оператор умножения вектора на матрицу
    TVector operator *(const TMatrix& arg) const;
    //оператор векторного умножения векторов
    TVector operator ^(const TVector& arg) const;
    //оператор умножения числа на вектор(число слева)
    friend TVector operator* (long double lvalue, const TVector& rvalue);
    //функция получения модуля вектора
    long double length() const;
    //функция нормирования вектора
    TVector GetNorm() const;
    inline TVector GetNegative() const {return (*this) * (-1);}
    // Поворот вектора вокруг заданной оси на заданный угол при помощи формулы Родрига
    TVector rotateByRodrigFormula(double phi, const TVector& axis) const;
    // Поворот вектора вокруг заданной оси на заданный угол при помощи кватерниона
    TVector rotate(double phi, const TVector& axis) const;
    // Поворот вектора при помощи заданного кватерниона
    TVector rotateByQuaternion(const TQuaternion& L) const;
};
class TMatrix:protected BaseMatrix{
private:
    inline TVector& operator() (size_t i) { return (TVector&)(*this)[i]; }
public:
    TMatrix():BaseMatrix(){}
    //Конструктор с заданным кол-вом элементов
    TMatrix(size_t n, size_t m) : BaseMatrix() { this->resize(n, m); }
    //конструктор копий
    TMatrix(const TMatrix& arg) : BaseMatrix(arg) {}
    //функция получения кол-ва строк
    inline size_t rowCount() const {return this->size(); }
    //Функция получения кол-ва столбцов
    inline size_t colCount() const {return (this->size() > 0) ? (*this)[0].size() : 0; }
    // Функция получения индекса последней строки
    inline size_t rowHigh() const { return rowCount() - 1; }
    // Функция получения индекса последнего столбца
    inline size_t colHigh() const { return colCount() - 1; }
    // оператор доступа к элементам матрицы
    inline long double& operator()(size_t i,size_t j){ return (*this)[i][j]; }
    // оператор константного доступа к элементам матрицы
    inline const long double& operator()(size_t i,size_t j) const { return (*this)[i][j]; }
    //константный оператор доступа к строке матрицы как к вектору
    //inline const TVector& operator() (size_t i) const { return (TVector&)(*this)[i]; }
    //изменение размера
    void resize(size_t n, size_t m);
    //унарный минус
    TMatrix operator - () const;
    //оператор вычитания матриц
    TMatrix operator - (const TMatrix& arg) const;
    //оператор сложения матриц
    TMatrix operator + (const TMatrix& arg) const;
    // Оператор умножения матрицы на число
    TMatrix operator * (long double arg) const;
    // Оператор умножения матриц
    TMatrix operator * (const TMatrix& arg) const;
    // Оператор умножения матрицы на вектор
    TVector operator * (const TVector& arg) const;
    // Дружественная функция - оператор умножения числа на матрицу
    friend TMatrix operator * (long double lvalue, const TMatrix& rvalue);
    // Оператор обращения матриц (метод Гаусса)
    TMatrix operator ! () const;
    // Функция вычисления детерминанта
    long double det() const;
    // Функция транспонирования
    TMatrix t() const;
    // Функция формирования единичной матрицы
    static TMatrix E(size_t n);
    // Функция перестановки строк
    TMatrix& swapRows(size_t i, size_t j);
    inline TMatrix GetNegative() const {return (*this) * (-1);}

};
class TSymmetricMatrix:public TMatrix{
protected:

public:
    TMatrix getLowerMatrix() const;

    TSymmetricMatrix(size_t n) : TMatrix() {this->resize(n,n);}

    inline TSymmetricMatrix t() const {}

    TSymmetricMatrix operator !() const;

    using TMatrix::operator =;


};

class TQuaternion {
    protected:
        //скалярная часть
        long double q0;
        //векторная часть
        TVector Q;
    public:
        //конструктор по умолчанию
        TQuaternion() : q0(0), Q(3){}
        //конструктор по компонентам квартениона
        TQuaternion(long double l0, long double l1, long double l2, long double l3);
        //конструктор по углу поворота (рад.) и оси вращения
        TQuaternion(long double phi, const TVector& e);
        //конструктор копирования
        TQuaternion(const TQuaternion& rvalue);
        //оператор присваивания
        TQuaternion& operator = (const TQuaternion& rvalue);
        //оператор вычитания кватернионов
        TQuaternion operator - (const TQuaternion& arg) const;
        // Оператор сложения кватернионов
        TQuaternion operator + (const TQuaternion& arg) const;
        // Оператор умножения кватернионов
        TQuaternion operator * (const TQuaternion& arg) const;
        // Оператор умножения кватерниона на вектор
        TQuaternion operator * (const TVector& arg) const;
        // Оператор умножения кватерниона на число
        TQuaternion operator * (long double arg) const;
        // Дружественная функция - оператор умножения числа на кватернион
        friend TQuaternion operator * (long double lvalue, const TQuaternion &rvalue);
        // Оператор обращения кватерниона
        TQuaternion operator ! () const;
        // Доступ к скалярной части
        inline double scal() const { return q0; }
        // Доступ к векторной части
        inline TVector vect() const { return Q; }
        // Функция нормирования кватерниона
        TQuaternion& norm();
        // Функция получения сопряженного кватерниона
        TQuaternion conj() const;
        // получение модуля кватерниона
        long double mod() const;
        // Функция получения матрицы вращения из компонентов кватерниона
        TMatrix toRotateMatrix() const;
        // Производящая функция для создания кватерниона по углам Крылова
        static TQuaternion fromKrylovAngles(long double yaw, long double pitch, long double roll);
};
}
#endif // TVECTOR_H
