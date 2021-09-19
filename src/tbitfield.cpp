// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
// Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
// Переработано в соответсвии с C++11 (частично) Пановым А.А. 2021
// Битовое поле

#include <limits>
#include <iostream>
#include "tbitfield.h"
#include <algorithm>
TBitField::TBitField() :pMem(nullptr), bitLen (0) ,memLen(0){}
TBitField::TBitField(size_t len ):memLen((bitLen + 31) >> 5),bitLen(len)
{ 
    pMem = new uint[memLen];
    for (int i = 0; i < memLen; ++i)
    {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    bitLen = bf.bitLen;
    memLen = bf.memLen;
    pMem = new uint[memLen];
    std::copy(bf.pMem, bf.pMem + memLen, pMem);
    

}

uint TBitField::getIndex(const size_t n) const  // индекс в pМем для бита n
{
    return n/(sizeof(uint)*8);
}

uint TBitField::getMask(const size_t n) const // битовая маска для бита n
{
    return ~(1u<<n);
}

// доступ к битам битового поля
uint TBitField::getLength() const // получить длину (к-во битов)
{   
    return bitLen;
}
void TBitField::setBit(const size_t n) // установить бит
{
    if (n >= bitLen)
    {
        EXCEPTION expt = outOFRANGE;
        throw expt;
    }
    size_t inside_index = n % (sizeof(uint) * 8);
    pMem[getIndex(n)] |= (1u<<inside_index);
}
void TBitField::clrBit(const size_t n) // очистить бит
{
    if (n >= bitLen)
    {
        EXCEPTION expt = outOFRANGE;
        throw expt;
    }
    size_t inside_index = n % (sizeof(uint) * 8);
    pMem[getIndex(n)] &=getMask(inside_index);
}

bool TBitField::getBit(const size_t n) const // получить значение бита
{
    if (n >= bitLen)
    {
        EXCEPTION expt = outOFRANGE;
        throw expt;
    }
    size_t inside_index = n % (sizeof(uint) * 8);
    return (bool)(pMem[getIndex(n)]&(1u<<inside_index));
}

// битовые операции
TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{   
    if (this != &bf)
    {
        bitLen = bf.bitLen;
        memLen = bf.memLen;
        delete[]pMem;
        pMem = new uint[memLen];
        std::copy(bf.pMem, bf.pMem + memLen, pMem);
    }
    return *this;
}

bool TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (memLen != bf.memLen)
        return false;
    for (int i = 0; i < memLen; ++i)
        {
        if (pMem[i] != bf.pMem[i])
            return false;
       }
    
    return true;
}

bool TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (memLen != bf.memLen)
        return true;
    for (int i = 0; i < memLen; ++i)
    {
        if (pMem[i] != bf.pMem[i])
            return true;
    }
    return false;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    uint q = std::max(bitLen, bf.bitLen);
    uint x = std::min(bitLen, bf.bitLen);
    TBitField tmp(q);
    for (int i = 0; i < x; ++i)
    {
       if(getBit(i) | bf.getBit(i))
           tmp.setBit(i);
    }
    if (bitLen > bf.bitLen)
    {
        for (int i = x; i < q; ++i)
        {
            if (getBit(i))
                tmp.setBit(i);
        }
    }
    if (bf.bitLen > bitLen)
{
    for (int i = x; i < q; ++i)
    {
        if (bf.getBit(i))
            tmp.setBit(i);
    }
}
    return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    uint q = std::max(bitLen, bf.bitLen);
    uint x = std::min(bitLen, bf.bitLen);
    TBitField tmp(q);
    for (int i = 0; i < x; ++i)
    {
        if (getBit(i) & bf.getBit(i))
            tmp.setBit(i);
    }
    return tmp;
}

TBitField TBitField::operator~() // отрицание
{
    TBitField tmp(bitLen);
    for (int i = 0; i < bitLen; ++i)
    {
        if (getBit(i) == false)
        {
            tmp.setBit(i);
        }
    }
    return tmp;
}

TBitField::~TBitField()
{
    delete[]pMem;
}

std::istream &operator>>(std::istream &istr, TBitField &bf) // ввод
{
    for (int i = 0; i < bf.memLen; ++i)
    {
        istr >> bf.pMem[i];
}
    return istr;
}

std::ostream &operator<<(std::ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.memLen; ++i)
    {
        for (int j = 0; j < bf.bitLen; ++j)
        {
           ostr << (bool)(bf.pMem[i] & (1u << j)) ;

        }
        ostr << std::endl;
}
    return ostr;
}
