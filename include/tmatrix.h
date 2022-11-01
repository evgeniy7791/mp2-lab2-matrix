// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    if (sz >= MAX_VECTOR_SIZE)
        throw out_of_range("VEctor size should be less than max vector size");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      sz = v.sz;
      pMem = new T[sz];
      std::copy(v.pMem, v.pMem + sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      this->sz = v.sz;
      this->pMem = v.pMem;
      v.pMem = nullptr;
      v.sz = 0;
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (*this == v)
          return *this;
      sz = v.sz;
      delete[]pMem;
      pMem = new T[sz];
      std::copy(v.pMem, v.pMem + sz, pMem);
      return *this;
      //
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      sz = v.sz;
      T* tmp = pMem;
      pMem = v.pMem;
      v.pMem = tmp;
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if ((ind < 0) || (ind >= sz))
       throw "error of index";
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if ((ind < 0) || (ind >= sz))
          throw "error of index";
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz) return false;
      for (size_t i = 0; i < sz; i++)
          if (pMem[i] != v.pMem[i]) return false;
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector<T> a(sz);
      for (size_t i = 0; i < sz; i++)
          a.pMem[i] += val;
      return a;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector a(sz);
      for (int i = 0; i < sz; i++)
          a.pMem[i] = pMem[i] - val;
      return a;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector<T> a(sz);
      for (size_t i = 0; i < sz; i++)
          a.pMem[i] = pMem[i] * val;
      return a;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw "Can`t add vectors with different sizes";
      TDynamicVector<T> a(sz);
      for (size_t i = 0; i < sz; i++)
         a.pMem[i] =pMem[i] + v.pMem[i];
      return a;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw "Can`t sub vectors with different sizes";
      TDynamicVector<T> a(sz);
      for (size_t i = 0; i < sz; i++)
         a.pMem[i] =pMem[i] - v.pMem[i];
          return a;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
      if (sz != v.sz)
          throw "Can`t mult vectors with different sizes";
      else {
          T result = 0.0;
          for (size_t i = 0; i < sz; i++)
              result = result + (pMem[i] * v.pMem[i]);
          return result;
      }
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  
    using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;

public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
      if (s >= MAX_MATRIX_SIZE)
          throw "too large matrix size";
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  TDynamicMatrix(const TDynamicVector<TDynamicVector<T>>& v) : TDynamicVector<TDynamicVector<T>>(v) {};

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::size;
  using TDynamicVector<TDynamicVector<T>>::at;

  TDynamicMatrix transpose(const TDynamicMatrix& m) {
      TDynamicMatrix a(m.sz);
      for (int i = 0; i < m.sz; i++)
          for (int j = 0; j < m.sz; j++)
              a[i][j] = m[j][i];
      return a;
  }


  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      return TDynamicVector<TDynamicVector<T>>::operator==(TDynamicVector<TDynamicVector<T>>(m));
  }
  bool operator!=(const TDynamicMatrix& m) const noexcept {
      return TDynamicVector<TDynamicVector<T>>::operator!=(TDynamicVector<TDynamicVector<T>>(m));
  }

  // матрично-скалярные операции
  TDynamicVector<T> operator*(const T& val)
  {
      return TDynamicVector<TDynamicVector<T>>::operator*(val);
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (size() != v.size())
          throw "exeption";
      TDynamicVector<T> tmp(size());
      for (size_t i = 0; i < size(); i++)
          tmp[i] = pMem[i] * v[i];
      return tmp;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (size() != m.size())
          throw "exeption";
      return TDynamicVector<TDynamicVector<T>>::operator+(TDynamicVector<TDynamicVector<T>>(m));

  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (size() != m.size())
          throw "exeption";
      return TDynamicVector<TDynamicVector<T>>::operator-(TDynamicVector<TDynamicVector<T>>(m));
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (size() != m.size())
          throw "exeption";
      TDynamicMatrix a(size());
      TDynamicMatrix b = transpose(m);
      for (int i = 0; i < m.sz; i++)
          for (int j = 0; j < m.sz; j++)
              a[i][j] = pMem[i] * b[j];
      return a;

  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          istr >> v.pMem[i]; // требуется оператор>> для типа T
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          ostr << v.pMem[i] << endl; // требуется оператор<< для типа T
      return ostr;
  }
};

#endif
