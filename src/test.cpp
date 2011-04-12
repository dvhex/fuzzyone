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
    LVar v;
    v.setTerm(0, new ShoulderTerm(0, 5));
    v.setTerm(1, new TriangularTerm(0, 5, 10));
    v.setTerm(2, new ShoulderTerm(5, 10, false));
    v = 18;
    cout << v.Value << endl;
    v.defuzzify();
    cout << v.Value << endl;
}

enum Energy {LOW, MEDIUM, HIGH};
enum Health {BAD, REGULAR, GOOD};

void testRule(LVar* o, LVarMap &in)
{
    LVar &out = *o;
    LVar &energy = *in[0];
    dout(out[BAD]     |= energy[LOW]);
    dout(out[REGULAR] |= energy[MEDIUM]);
    dout(out[GOOD]    |= energy[HIGH]);
}

void testFuzzyOne()
{
    FuzzyOne fuzzy;
    LVar *energy = new LVar;
    energy->setTerm(LOW,    new   ShoulderTerm(0.25, 0.50, true));
    energy->setTerm(MEDIUM, new TriangularTerm(0.25, 0.50, 0.75));
    energy->setTerm(HIGH,   new   ShoulderTerm(0.50, 0.75, false));
    fuzzy.setInputLVar(0, energy);
    LVar *health = new LVar;
    health->setTerm(BAD,     new TriangularTerm(0.0,  0.25, 0.50));
    health->setTerm(REGULAR, new TriangularTerm(0.25, 0.50, 0.75));
    health->setTerm(GOOD,    new TriangularTerm(0.50, 0.75, 1.00));
    fuzzy.setOutputLVar(health);
    fuzzy.setRule(testRule);
    for (double x=0.0; x<1.1; x+=0.1)
    {
        *fuzzy[0] = x;
        fuzzy.run();
        cout << x << '\t' << fuzzy.out()->Value << endl;
    }
}

int main()
{
    //testFuzzyType();
    //testTerm();
    //testLVar();
    testFuzzyOne();
    return 0;
}
