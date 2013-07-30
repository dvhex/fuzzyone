#include <cmath>

#include "Term.h"
#include "Exception.h"

Fuzzy::BaseTerm::BaseTerm(double a, double b)
{
    if (a > b)
        throw Exception("Error parameters");
    pA = a;
    pB = b;
}

Fuzzy::TriangularTerm::TriangularTerm(double a, double b, double c)
    : BaseTerm(a,b)
{
    if (b > c)
        throw Exception("Error parameters");
    pC = c;
}

Fuzzy::FuzzyType
Fuzzy::TriangularTerm::Calc(double x) const
{
    if (x <= pA || x > pC)
        return 0;
    if (x <= pB)
        return (x - pA) / (pB - pA);
    else
        return (x - pC) / (pB - pC);
}

Fuzzy::ShoulderTerm::ShoulderTerm(double a, double b, bool left)
    : BaseTerm(a,b)
{
    pLeft = left;
}

Fuzzy::FuzzyType
Fuzzy::ShoulderTerm::Calc(double x) const
{
    if (x <= pA)
    {
        if (!pLeft)
            return 0;
        else
            return 1;
    }
    if (x > pB)
    {
        if (pLeft)
            return 0;
        else
            return 1;
    }
    if (pLeft)
        return (x - pB) / (pA - pB);
    else
        return (x - pA) / (pB - pA);
}

Fuzzy::FuzzyType
Fuzzy::STerm::Calc(double x) const
{
    double value;
    double c = (pA + pB) / 2;
    if (x <= pA)
        value = 0;
    else if (x <= c)
        value = 2.0 * std::pow((x - pA) / (pB - pA), 2);
    else if (x <= pB)
        value = 1.0 - 2.0 * std::pow((x - pB) / (pB - pA), 2);
    else
        value = 1.0;
    if (pLeft)
        return 1.0 - value;
    else
        return value;
}

Fuzzy::FuzzyType
Fuzzy::PTerm::Calc(double x) const
{
    STerm leftS(pA, pB, false);
    STerm rightS(pB, pC, true);
    if (x < pB)
        return leftS.Calc(x);
    else
        return rightS.Calc(x);
}