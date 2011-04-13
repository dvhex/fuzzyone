#include "Hedge.h"
#include "Term.h"
#include <cmath>

Fuzzy::FuzzyType
Fuzzy::Hedge::operator()(const Term *term, double x) const
{
    return operator()(term->Calc(x));
}

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
