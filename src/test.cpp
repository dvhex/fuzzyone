#include "FuzzyOne.cpp"
#include <iostream>

using namespace std;
using Fuzzy::FuzzyType;

#define dout(arg) cout << #arg" = " << (arg) << endl

int main()
{
    FuzzyType a(0.4);
    FuzzyType b(0.9);
    dout(a);
    dout(b);
    dout(a + b);
    dout(a - b);
    dout(a * b);
    dout(a & b);
    dout(a | b);
    dout(~a);
    return 0;
}
