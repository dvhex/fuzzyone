#include "FuzzyOne.h"
#include "Term.h"
#include "Hedge.h"
#include "LVar.h"
#include <iostream>

using namespace std;
using namespace Fuzzy;

#define dout(arg) cout << #arg" = " << (arg) << endl

void testFuzzyType()
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
}

void testTerm()
{
    TriangularTerm t(0, 5, 10);
    cout << "Triangular term:" << endl;
    for (int i=0; i<=10; i++)
        cout << i << '\t' << t.Calc(i) << endl;
    ShoulderTerm s(2, 8);
    cout << "Shoulder term:" << endl;
    for (int i=0; i<=10; i++)
        cout << i << '\t' << s.Calc(i) << endl;
    cout << "Over:" << endl;
    HedgeVery v;
    for (int i=0; i<=10; i++)
        cout << i << '\t' << v(s(i)) << endl;
}

void testLVar()
{
    InputLVar v;
    v.setTerm(0, new ShoulderTerm(0, 5));
    v.setTerm(1, new TriangularTerm(0, 5, 10));
    v.setTerm(2, new ShoulderTerm(5, 10, false));
    v = 18;
    cout << v.Value << endl;
    v.defuzzify();
    cout << v.Value << endl;
}

int main()
{
    //testFuzzyType();
    //testTerm();
    testLVar();
    return 0;
}
