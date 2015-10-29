﻿// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
  ValType *pVector;
  int Size;       // размер вектора
  int StartIndex; // индекс первого элемента вектора
public:
	TVector( int s = 10, int si = 0);
  TVector(const TVector &v);                // конструктор копирования
  virtual ~TVector();
  int GetSize() const       { return Size;       } // размер вектора
  int GetStartIndex() const { return StartIndex; } // индекс первого элемента
  ValType& operator[](int pos) const;             // доступ
  bool operator==(const TVector &v) const;  // сравнение
  bool operator!=(const TVector &v) const;  // сравнение
  TVector& operator=(const TVector &v);     // присваивание

  // скалярные операции
  TVector  operator+(const ValType &val);   // прибавить скаляр
  TVector  operator-(const ValType &val);   // вычесть скаляр
  TVector  operator*(const ValType &val);   // умножить на скаляр

  // векторные операции
  TVector  operator+(const TVector &v);     // сложение
  TVector  operator-(const TVector &v);     // вычитание
  ValType  operator*(const TVector &v);     // скалярное произведение

  // ввод-вывод
  friend istream& operator>>(istream &in, TVector &v)
  {
    for (int i = 0; i < v.Size; i++)
      in >> v.pVector[i];
    return in;
  }
  friend ostream& operator<<(ostream &out, const TVector &v)
  {
    for (int i = 0; i < v.Size + v.StartIndex; i++)
      out << v[i] << ' ';
    return out;
  }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si = 0)
{
	if (s>MAX_VECTOR_SIZE)
	{
		throw invalid_argument("Конструктор MAX_VECTOR_SIZE<s");
	}
	if (s<0)
	{
		throw invalid_argument("Конструктор s<0");
	}
	if (si<0){
		throw invalid_argument("Конструктор si<0");
	}
	pVector = new ValType[s];
	Size = s;
	StartIndex = si;
	for (int i = StartIndex; i < Size+StartIndex; i++)
	{
		(*this)[i] = ValType();
	}

} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{
	Size = v.Size;
	StartIndex = v.StartIndex;
	pVector = new ValType[Size];

	for (int i = 0; i < Size; i++) {
		pVector[i] = v.pVector[i];
	}

} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
	delete []pVector;
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos) const
{
	if (pos<0)
	{
		throw invalid_argument("[] pos<0");
	}
	if (pos>=StartIndex+Size)
	{
		throw invalid_argument("[] pos>MAX_VECTOR_SIZE");
	}
	if (pos<StartIndex) {
		return *new ValType();
	}
	return pVector[pos-StartIndex];
} /*-------------------------------------------------------------------------*/


template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
	if (Size != v.GetSize())
	{
		return false;
	}
	if (StartIndex != v.GetStartIndex()) {
		return false;
	}
	
	for (int i = StartIndex; i < Size + StartIndex; i++) {
		if ((*this)[i] != v[i]) {
			return false;
		}
	}
	return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
	return !(*this==v);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v) 
{
	if (this != &v)
	{
		if (Size != v.GetSize())
		{
			delete[]pVector;
			pVector = new ValType[v.Size];
		}
		Size = v.GetSize();
		StartIndex = v.GetStartIndex();
		for (int i = StartIndex; i < Size+StartIndex; i++)
		{
			(*this)[i] = v[i];
		}
	}
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
	for (int i = StartIndex; i < Size + StartIndex; i++) {
		(*this)[i] = (*this)[i] + val;
	}
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
	for (int i = StartIndex; i < Size + StartIndex; i++) {
		(*this)[i] = (*this)[i] - val;
	}
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
	for (int i = StartIndex; i < Size + StartIndex; i++)
	{
		(*this)[i] = (*this)[i] * val;
	}

	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
	
	if (GetSize() != v.GetSize() || GetStartIndex() != v.GetStartIndex())
	{
		throw invalid_argument("Сложение векторов разной длины");
	}

	TVector<ValType> result(GetSize(), GetStartIndex());

	for (int i = StartIndex; i < Size + StartIndex; i++) {
		result[i] = (*this)[i] + v[i];
	}
	return result;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
	if (GetSize() == v.GetSize()) {
		TVector<ValType> result(GetSize(),GetStartIndex());

		for (int i = StartIndex; i < Size + StartIndex; i++) {
			result[i] = (*this)[i] - v[i];
		}
		return result;
	}
	throw invalid_argument("Вычитание векторов разной длины");
} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
	ValType result=0;
	if (GetSize() == v.GetSize()) {
		for (int i = StartIndex; i < Size + StartIndex; i++) {
			result = result + (*this)[i] * v[i];
		}
		return result;
	}
	throw invalid_argument("Скалярное произведение векторов разной длины");
} /*-------------------------------------------------------------------------*/


// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
  TMatrix(int s = 10);                           
  TMatrix(const TMatrix &mt);                    // копирование
  TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа

  bool operator==(const TMatrix &mt) const;      // сравнение
  bool operator!=(const TMatrix &mt) const;      // сравнение
  TMatrix& operator= (const TMatrix &mt);        // присваивание
  TMatrix  operator+ (const TMatrix &mt);        // сложение
  TMatrix  operator- (const TMatrix &mt);        // вычитание
  TMatrix  operator* (const TMatrix &mt);		 // умножение

  // ввод / вывод
  friend istream& operator>>(istream &in, TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      in >> mt.pVector[i];
    return in;
  }
  friend ostream & operator<<( ostream &out, const TMatrix &mt)
  {
    for (int i = 0; i < mt.Size + mt.GetStartIndex(); i++)
      out << mt[i] << endl;
    return out;
  }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s): TVector<TVector<ValType> >(s)
{
	if (s<0)
	{
		throw invalid_argument("s<0 в Matrix");
	}
	if (s>MAX_MATRIX_SIZE) {
		throw invalid_argument("MAX_MATRIX_SIZE<s в Matrix");
	}
	for (int i = 0; i < s; i++) {
		pVector[i] = TVector<ValType>(s-i, i);
	}

	for (int i = 0; i < s; i++) {
		for (int j = (*this)[i].GetStartIndex(); j < (*this)[i].GetStartIndex() + (*this)[i].GetSize(); j++) {
			pVector[i][j] = 0;
		}
	}
} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt) : TVector<TVector<ValType> >(mt)
{}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):
  TVector<TVector<ValType> >(mt) {}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
	if (this == &mt) {
		return true;
	}

	if (Size != mt.GetSize()) {
		return false;
	}

	for (int i = 0; i < Size; i++) {
		if (pVector[i] != mt.pVector[i])
			return false;
	}

	return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение !=
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
	return !(*this==mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
	if (this != &mt) {
		if (Size != mt.Size) {
			delete[] pVector;
			pVector = new TVector<ValType>[mt.Size];
		}
		Size = mt.Size;
		StartIndex = mt.StartIndex;
		for (int i = 0; i < Size; i++)
			pVector[i] = mt.pVector[i];
	}
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
	if (Size!=mt.GetSize())
	{
		throw invalid_argument("Матрицы разного размера +");
	}
	TMatrix<ValType> result(Size);
	for (int i = 0; i < Size; i++)
	{
		result[i] = (*this)[i] + mt[i];
	}
	return result;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
	if (Size != mt.GetSize()) {
		throw invalid_argument("Матрицы разного размера -");
	}
	TMatrix<ValType> result(Size);
	for (int i = 0; i < Size; i++) {
		result[i] = (*this)[i] - mt[i];
	}
	return result;
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножение
TMatrix<ValType> TMatrix<ValType>::operator* (const TMatrix<ValType> &mt) {
	if (Size != mt.GetSize()) {
		throw invalid_argument("Матрицы разного размера -");
	}
	TMatrix<ValType> result(Size);
	for (int i = 0; i < this->GetSize(); i++)
		for (int j = i; j < this->GetSize(); j++)
			for (int k = 0; k <= j; k++)
				result[i][j] = result[i][j] + ((*this)[i][k])*(mt[k][j]);
	return result;
} /*-------------------------------------------------------------------------*/

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
