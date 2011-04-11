#include "LVar.h"
#include "Exception.h"

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
Fuzzy::InputLVar::fuzzify(double x)
{
    for (map<int,Term*>::iterator iter = pTerms.begin(),
            end = pTerms.end(); iter != end; iter++)
    {
        iter->Set(x);
    }
}
