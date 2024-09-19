// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
    this->MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
    this->MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
    this->MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
    return this->BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return this->MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return this->BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    this->BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    this->BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    if (this == &s) return *this;
    this->MaxPower = s.MaxPower;
    this->BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return this->BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return this->BitField != s.BitField;
}

TSet TSet::operator+(const TSet &s) // объединение
{
    return TSet(this->BitField|s.BitField);
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet ts(this->MaxPower);
    ts.InsElem(Elem);
    return TSet(this->BitField|ts.BitField);
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet ts(this->BitField);
    ts.DelElem(Elem);
    return ts;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    return TSet(this->BitField&s.BitField);
}

TSet TSet::operator~(void) // дополнение
{
    TSet ts(this->BitField);
    ~(ts.BitField);
    return TSet(~(this->BitField));
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    ostr << "{";
    for (int i = 0; i < s.MaxPower; i++) if (s.BitField.GetBit(i) == 1) ostr << " " << i << " ";
    ostr << "}";
    return ostr;
}
