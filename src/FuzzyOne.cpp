#include "FuzzyOne.h"

Fuzzy::FuzzyOne::FuzzyOne()
{
    //ctor
}

Fuzzy::FuzzyOne::~FuzzyOne()
{
    //dtor
}

Fuzzy::FuzzyType::FuzzyType(double arg)
{
    if (arg > 1)
        v = 1;
    else if (arg <= 0)
        v = 0;
    else
        v = arg;
}

Fuzzy::FuzzyType&
Fuzzy::FuzzyType::operator+=(Fuzzy::FuzzyType arg)
{
    v = v + arg - v * arg;
    return *this;
}

Fuzzy::FuzzyType&
Fuzzy::FuzzyType::operator-=(Fuzzy::FuzzyType arg)
{
    return operator&=(arg.operator~());
}

Fuzzy::FuzzyType&
Fuzzy::FuzzyType::operator*=(Fuzzy::FuzzyType arg)
{
    v *= arg;
    return *this;
}

Fuzzy::FuzzyType&
Fuzzy::FuzzyType::operator&=(Fuzzy::FuzzyType arg)
{
    if (arg < v)
        v = arg;
    return *this;
}

Fuzzy::FuzzyType&
Fuzzy::FuzzyType::operator|=(Fuzzy::FuzzyType arg)
{
    if (arg > v)
        v = arg;
    return *this;
}

Fuzzy::FuzzyType
Fuzzy::FuzzyType::operator~() const
{
    FuzzyType tmp(*this);
    tmp.v = 1.0 - v;
    return tmp;
}

Fuzzy::FuzzyType
Fuzzy::FuzzyType::operator+(Fuzzy::FuzzyType arg) const
{
    FuzzyType tmp(*this);
    tmp += arg;
    return tmp;
}

Fuzzy::FuzzyType
Fuzzy::FuzzyType::operator-(Fuzzy::FuzzyType arg) const
{
    FuzzyType tmp(*this);
    tmp -= arg;
    return tmp;
}

Fuzzy::FuzzyType
Fuzzy::FuzzyType::operator*(Fuzzy::FuzzyType arg) const
{
    FuzzyType tmp(*this);
    tmp *= arg;
    return tmp;
}

Fuzzy::FuzzyType
Fuzzy::FuzzyType::operator&(Fuzzy::FuzzyType arg) const
{
    FuzzyType tmp(*this);
    tmp &= arg;
    return tmp;
}

Fuzzy::FuzzyType
Fuzzy::FuzzyType::operator|(Fuzzy::FuzzyType arg) const
{
    FuzzyType tmp(*this);
    tmp |= arg;
    return tmp;
}
