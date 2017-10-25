// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if(len<=0)
		throw len;
	BitLen=len;
	MemLen=BitLen/ (sizeof(TELEM)) + 1;
	pMem=new TELEM[MemLen];
	for (int i=0; i<MemLen; i++)
		pMem[i]=0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen=bf.BitLen;
	MemLen=bf.MemLen;
	pMem=new TELEM[MemLen];
	for(int i=0; i<MemLen; i++)
		pMem[i]=bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n<0) || (n>=BitLen))
		throw n;
	return n/(sizeof(TELEM)*8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n<0) || (n>=BitLen))
		throw n;
	return 1<<n%(sizeof(TELEM)*8);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n<0) || (n>=BitLen))
		throw n;

	int GMI=GetMemIndex(n);
	TELEM GMM=GetMemMask(n);
	pMem[GMI]|=GMM;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n<0) || (n>=BitLen))
		throw n;

	int GMI=GetMemIndex(n);
	TELEM GMM=GetMemMask(n);
	pMem[GMI]&= ~GMM;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n<0) || (n>=BitLen))
		throw n;

	int GMI=GetMemIndex(n);
	TELEM GMM=GetMemMask(n);
	GMM &= pMem[GMI];
	if (GMM!=0)
		return 1;
	else
		return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	int a,b;
	if (MemLen!=bf.MemLen) {
		delete[] pMem;
		MemLen=bf.MemLen;
		pMem=new TELEM [MemLen];
	}
	BitLen=bf.BitLen;
	for (int i=0; i<MemLen; i++){
		pMem[i]=bf.pMem[i];
		a=pMem[i];
		b=bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen!=bf.BitLen)
		return 0;
	int i;
	for (i=0; i<MemLen; i++)
		if (pMem[i]!=bf.pMem[i])
			return 0;
	for (i=(MemLen-1)*sizeof(TELEM); i<BitLen; i++)
		if (GetBit(i)!=bf.GetBit(i))
			return 0;
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	return !((*this)==bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int max_len=BitLen;
	int min_len=BitLen;

	if(BitLen!=bf.BitLen) 
		if(BitLen<bf.BitLen){
			max_len=bf.BitLen;
			min_len=BitLen;
		}
		else {
			max_len=BitLen;
			min_len=BitLen;
		}

	TBitField tmp(max_len);
	for (int i=0; i<MemLen; i++)
		tmp.pMem[i]=pMem[i] | bf.pMem[i];
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int max_len=BitLen;
	int min_len=BitLen;

	if(BitLen!=bf.BitLen) 
		if(BitLen<bf.BitLen){
			max_len=bf.BitLen;
			min_len=BitLen;
		}
		else {
			max_len=BitLen;
			min_len=BitLen;
		}

	TBitField tmp(max_len);
	for (int i=0; i<MemLen; i++)
		tmp.pMem[i]=pMem[i] & bf.pMem[i];
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	int buf;
	TBitField tmp(BitLen);
	for (int i=0; i<MemLen; i++) {
		if(pMem[i]==1)
			buf=0;
		else
			buf=1;
		tmp.pMem[i]=buf;
	}
		
	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int i=0;
	char ch;
	do {
		istr >> ch;
	} while (ch!= ' ');
	while (1) {
		istr >> ch;
		if ( ch == '0' ) 
			bf.ClrBit(i++);
		else 
			if (ch == '1') 
				bf.ClrBit(i++);
		else 
			break;
	}
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
		if (bf.GetBit(i) == 1)
			ostr << 1  << ' ';
		else
			ostr << 0  << ' ';
	return ostr;
}
