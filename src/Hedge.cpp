#include "Hedge.h"
#include <cmath>

Fuzzy::FuzzyType
Fuzzy::HedgeVery::operator()(FuzzyType v) const
{
    return std::pow(v, 2);
}

Fuzzy::FuzzyType
Fuzzy::HedgeSomewat::operator()(FuzzyType v) const
{
    return sqrt(v);
}

Fuzzy::FuzzyType
Fuzzy::HedgeAny::operator()(FuzzyType v) const
{
    return v?1:0;
}
