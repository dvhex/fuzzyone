#include "LVar.h"
#include "Exception.h"
#include <cmath>

using std::map;

Fuzzy::LVar::~LVar()
{
    for (map<int,Term*>::iterator iter = pTerms.begin(),
            end = pTerms.end(); iter != end; ++iter)
    {
        delete iter->second;
    }
}

Fuzzy::FuzzyType&
Fuzzy::LVar::operator[](int index)
{
    map<int,Term*>::iterator iter = pTerms.find(index);
    if (iter != pTerms.end())
        return iter->second->Value;
    else
        throw Exception("Term don't exists");
}

void
Fuzzy::LVar::zero()
{
    for (TermsMap::iterator iter = pTerms.begin(),
            end = pTerms.end(); iter != end; ++iter)
        iter->second->Value = 0;
}

void
Fuzzy::LVar::defuzzify()
{
    double min = INFINITY;
    double max = -min;
    for (TermsMap::const_iterator iter = pTerms.begin(),
            end = pTerms.end(); iter != end; ++iter)
    {
        if (iter->second->min() < min)
            min = iter->second->min();
        if (iter->second->max() > max)
            max = iter->second->max();
    }
    double h = (max - min) / 1000;
    double a = 0, b = 0, x = min;
    while (x <= max)
    {
        double y = 0;
        for (TermsMap::const_iterator iter = pTerms.begin(),
                end = pTerms.end(); iter != end; ++iter)
        {
            y = std::max((double)std::min(iter->second->Value, iter->second->Calc(x)), y);
        }
        a += x * y;
        b += y;
        x += h;
    }
    Value = a / b;
}

void
Fuzzy::InputLVar::fuzzify(double x)
{
    Value = x;
    for (map<int,Term*>::iterator iter = pTerms.begin(),
            end = pTerms.end(); iter != end; iter++)
    {
        iter->second->Set(x);
    }
}
