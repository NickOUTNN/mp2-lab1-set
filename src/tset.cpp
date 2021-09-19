// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
// Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
// Переработано в соответсвии с C++11 (частично) Пановым А.А. 2021
// Множество - реализация через битовые поля
#include <algorithm>
#include <iostream>
#include "tbitfield.h"
#include "tset.h"

TSet::TSet(size_t mp) : bitField(mp),maxPower(mp) {}

// конструктор копирования
TSet::TSet(const TSet &s) : bitField(s.bitField), maxPower(s.maxPower) {}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : bitField(bf), maxPower(bf.getLength()) {}

TSet::operator TBitField()
{
    TBitField tmp(bitField);
    return tmp;
}

size_t TSet::getMaxPower() const // получить макс. к-во эл-тов
{
    return maxPower;
}

bool TSet::isMember(const uint elem) const // элемент множества?
{
    if (this->bitField.getBit(elem))
        return true;
    return false;
}

void TSet::insElem(const uint elem) // включение элемента множества
{
    bitField.setBit(elem);
}

void TSet::delElem(const uint elem) // исключение элемента множества
{
    bitField.clrBit(elem);
}

// теоретико-множественные операции
TSet& TSet::operator=(const TSet &s) // присваивание
{
    if (this != &s)
    {
        maxPower = s.maxPower;
        bitField = s.bitField;
}
    return *this;
}

bool TSet::operator==(const TSet& s) const // сравнение
{
    if (maxPower != s.maxPower)
        return false;
    if (bitField != s.bitField)
        return false;
    return true;

}

bool TSet::operator!=(const TSet &s) const // сравнение
{
    if (maxPower != s.maxPower)
        return true;
    if (bitField != s.bitField)
        return true;
    return false;
}

TSet TSet::operator+(const TSet &s) // объединение
{
    uint l = std::max(maxPower,s.maxPower);
    TSet tmp(l);
    tmp.bitField = bitField | s.bitField;
    return tmp;
}

TSet TSet::operator+(const uint elem) // объединение с элементом
{
    TBitField tmpBit(maxPower);
    TSet tmp(maxPower);
    tmpBit.setBit(elem);
    tmp.bitField = bitField | tmpBit;
    return tmp;
}

TSet TSet::operator-(const uint elem) // разность с элементом
{  
    TBitField k(maxPower);
    TSet tmp(maxPower);
    k.setBit(elem);
    tmp.bitField = bitField & ~k;
    return tmp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    uint l = std::max(maxPower,s.maxPower);
    TSet tmp(l);
    tmp.bitField = bitField & s.bitField;
    return tmp;
}

TSet TSet::operator~() // дополнение
{
    TSet tmp(*this);
    tmp.bitField = ~bitField;
    return tmp;
}


std::istream &operator>>(std::istream &istr, TSet &s) // ввод
{
    istr >> s.bitField;
    return istr;
}

std::ostream &operator<<(std::ostream &ostr, const TSet &s) // вывод
{
    ostr << s.bitField;
    return ostr;
}
