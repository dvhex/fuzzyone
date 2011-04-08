#include "Term.h"
#include "Exception.h"

Fuzzy::TriangularTerm::TriangularTerm(FuzzyType a, FuzzyType b, FuzzyType c)
{
    if (a > b || b > c)
        throw Exception("Error parameters");
    pA = a;
    pB = b;
    pC = c;
}

FuzzyType
Fuzzy::TriangularTerm::Get(FuzzyType x)
{
    if (x <= pA || x > pC)
        return 0;
    if (x <= pB)
        return (x - pA) / (pB - pA);
    else
        return (x - pC) / (pB - pC);
}

Fuzzy::ShoulderTerm::ShoulderTerm(FuzzyType a, FuzzyType b, bool left)
{
    if (a > b)
        throw Exception("Error parameters");
    pA = a;
    pB = b;
    pLeft = left;
}

FuzzyType
Fuzzy::ShoulderTerm::Get(FuzzyType x)
{
    if (x <= pA)
        if (!pLeft)
            return 0;
        else
            return 1;
    if (x > pB)
        if (pLeft)
            return 0;
        else
            return 1;
    if (pLeft)
        return (x - pB) / (pA - pB);
    else
        return (x - pA) / (pB - pA);
}
