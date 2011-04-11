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
Fuzzy::TriangularTerm::Calc(double x)
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
Fuzzy::ShoulderTerm::Calc(double x)
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
