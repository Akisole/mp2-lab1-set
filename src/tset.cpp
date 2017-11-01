// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	MaxPower=mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
	MaxPower=s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(-1)
{
}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return BitField.GetLength();
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	if (BitField.GetBit(Elem)==1)
		return Elem;
	else 
		return 0;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if(Elem>MaxPower)
		throw -1;
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	BitField=s.BitField;
	MaxPower=s.MaxPower;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (MaxPower!=s.MaxPower)
		return 0;
	if (BitField!=s.BitField)
	    return 0;
	else
		return 1;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	return !((*this)==s);
}

TSet TSet::operator+(const TSet &s) // объединение
{
	int max_MP=MaxPower;

	if(MaxPower!=s.MaxPower)
		if(MaxPower<s.MaxPower)
			max_MP=s.MaxPower;
		
	TSet res(max_MP);
	TBitField TBBuf=BitField|s.BitField;
	res.BitField=TBBuf;
	return res;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet res(*this);
	res.InsElem(Elem);
	return res;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet res(BitField);
	res.DelElem(Elem);
	return res;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	int max_MP=MaxPower;

	if(MaxPower!=s.MaxPower)
		if(MaxPower<s.MaxPower)
			max_MP=s.MaxPower;
		
	TSet res(max_MP);
	TBitField TBBuf=BitField&s.BitField;
	res.BitField=TBBuf;
	return res;
}

TSet TSet::operator~(void) // дополнение
{
	TSet tmp(MaxPower);
	for(int i=0; i<MaxPower; i++)
		if(!IsMember(i))
			tmp.InsElem(i);
	return tmp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int n;
	do {
		istr >> n;
	} while (n>=0); 
	while (n>=0) {
		s.InsElem(n);
		istr>>n;
	}
	
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	for (int i = 0; i < s.MaxPower; i++)
		if (s.IsMember(i)!=0)
			ostr << i << ' ';
	return ostr;
}
