// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
    if (len < 0) throw "incorrect size";
    this->BitLen = len;
    this->MemLen = (BitLen + sizeof(TELEM) * 8 - 1) / (sizeof(TELEM) * 8);
    this->pMem = new TELEM[MemLen];
    for(int i = 0; i < MemLen; i++) this->pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    this->BitLen = bf.BitLen;
    this->MemLen = bf.MemLen;
    this->pMem = new TELEM[MemLen];

    for (int i = 0; i < MemLen; i++) this->pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
    delete[] this->pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return this->MemLen - n / (sizeof(TELEM) * 8) - 1;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return 1 << n % (sizeof(TELEM) * 8);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return this->BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0 || n >= BitLen) throw "incorrect index";
    this->pMem[this->GetMemIndex(n)] |= this->GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0 || n >= BitLen) throw "incorrect index";
    this->pMem[this->GetMemIndex(n)] &= ~(this->GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0 || n >= BitLen) throw "incorrect index";
    TELEM temp = this->pMem[this->GetMemIndex(n)] & this->GetMemMask(n);
    if(temp == 0) return 0;
    return 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this == &bf) return *this;
    else {
        this->BitLen = bf.BitLen;
        this->MemLen = bf.MemLen;
        delete[] this->pMem;
        this->pMem = new TELEM[this->MemLen];
        for (int i = 0; i < this->MemLen; i++) this->pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (this->BitLen != bf.BitLen) return 0;
    for (int i = 0; i < this->BitLen; i++) if (this->GetBit(i) != bf.GetBit(i)) return 0;
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (*this == bf) return 0;
    else return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int m = this->BitLen, n = this->BitLen;
    if (m > bf.BitLen) m = bf.BitLen;
    if (n < bf.BitLen) n = bf.BitLen;

    TBitField tbf(n);

    for (int i = 0; i < n; i++) {
        if (i >= this->BitLen) { if (bf.GetBit(i) == 1) tbf.SetBit(i); }
        else if (i >= bf.BitLen) { if (this->GetBit(i) == 1) tbf.SetBit(i); }
        else if ((this->GetBit(i) | bf.GetBit(i)) == 1) tbf.SetBit(i);
    }
    return tbf;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int m = this->BitLen, n = this->BitLen;
    if (m > bf.BitLen) m = bf.BitLen;
    if (n < bf.BitLen) n = bf.BitLen;

    TBitField tbf(n);

    for (int i = 0; i < m; i++) {
        if ((this->GetBit(i) & bf.GetBit(i)) == 1) tbf.SetBit(i);
    }
    return tbf;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField tbf(this->BitLen);
    for (int i = 0; i < this->MemLen; i++) tbf.pMem[i] = ~(this->pMem[i]);
    return tbf;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    int bit;
    for (int i = 0; i < bf.BitLen; i++) {
        istr >> bit;
        if (bit == 1) bf.SetBit(bf.BitLen - i - 1);
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++) ostr << bf.GetBit(bf.BitLen - i - 1);
    return ostr;
}
