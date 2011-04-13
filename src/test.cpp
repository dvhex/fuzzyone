#include "FuzzyOne.h"
#include "Term.h"
#include "Hedge.h"
#include "LVar.h"
#include <iostream>
#include <cmath>

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
    SimpleHedgeTerm vt(s, new HedgeVery());
    for (int i=0; i<=10; i++)
        cout << i << '\t' << vt(i) << endl;
}

void testLVar()
{
    LVar v, e;
    v.setTerm(0, new ShoulderTerm(0, 5));
    v.setTerm(1, new TriangularTerm(0, 5, 10));
    v.setTerm(2, new ShoulderTerm(5, 10, false));
    e.setTerm(0, new ShoulderTerm(0, 10));
    e.setTerm(1, new ShoulderTerm(0, 10, false));
    e.zero();
    v = 18;
    dout(v[0]);
    dout(v[1]);
    dout(v[2]);
    dout(e[0] = v[0] | v[1]);
    dout(e[1] = v[1] | v[2]);
    cout << v.Value << endl;
    e.defuzzify();
    cout << e.Value << endl;
}

namespace test{
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
}

namespace rating
{

    enum modifers{NEGATIVE=-1, NONE=0, LOW=1, MEDIUM=2, HIGH=3, HIGHER=4, NOT_LOW, VERY_HIGH};

    double calc(double p, double dd, double l)
    {
        static LVar drawdown, profit, lot, rating;
        static bool start = true;
        if (start)
        {
            drawdown.setTerm(LOW,      new   ShoulderTerm(  0.0, 20.0, true));
            drawdown.setTerm(MEDIUM,   new TriangularTerm(  0.0, 20.0, 40.0));
            drawdown.setTerm(HIGH,     new TriangularTerm( 20.0, 40.0, 80.0));
            drawdown.setTerm(HIGHER,   new   ShoulderTerm( 40.0, 80.0,false));
              profit.setTerm(NEGATIVE, new   ShoulderTerm( -0.2,  0.0, true));
              profit.setTerm(NONE,     new TriangularTerm( -0.2,  0.0,  0.2));
              profit.setTerm(LOW,      new TriangularTerm(  0.0,  0.2,  1.0));
              profit.setTerm(MEDIUM,   new TriangularTerm(  0.2,  1.0,  4.5));
              profit.setTerm(HIGH,     new TriangularTerm(  1.0,  4.5, 19.58));
              profit.setTerm(HIGHER,   new   ShoulderTerm(  4.5, 19.58,false));
                 lot.setTerm(LOW,      new   ShoulderTerm(  0.0,  0.1, true));
                 lot.setTerm(MEDIUM,   new TriangularTerm(  0.0,  0.1,  0.3));
                 lot.setTerm(HIGH,     new TriangularTerm(  0.1,  0.3,  1.0));
                 lot.setTerm(HIGHER,   new   ShoulderTerm(  0.3,  1.0,false));

               ShoulderTerm *lrating = new   ShoulderTerm(-25.0, 50.0, true);
               ShoulderTerm *hrating = new   ShoulderTerm( 50.0,125.0,false);
              rating.setTerm(LOW,      lrating);
              rating.setTerm(MEDIUM,   new TriangularTerm(-25.0, 50.0,125.0));
              rating.setTerm(HIGH,     hrating);
              rating.setTerm(NOT_LOW, new SimpleHedgeTerm(*lrating, new HedgeNot()));
              rating.setTerm(VERY_HIGH, new SimpleHedgeTerm(*hrating, new HedgeVery()));
        }
        p = log10(p / 100.0 + 1.0) * 24.1589;
        profit = p;
        drawdown = dd;
        lot = l;

        //правила
        rating.zero();
        rating[LOW] |= profit[NEGATIVE] | profit[NONE] | profit[LOW]
            | drawdown[HIGHER] | lot[HIGHER];
        rating[MEDIUM] |= profit[MEDIUM] & drawdown[LOW];
        rating[MEDIUM] |= profit[MEDIUM] & drawdown[MEDIUM] & lot[LOW];
        rating[NOT_LOW]|= profit[MEDIUM] & drawdown[MEDIUM] & lot[MEDIUM];
        rating[LOW]    |= profit[MEDIUM] & drawdown[MEDIUM] & lot[HIGH];
        rating[LOW]    |= profit[MEDIUM] & drawdown[HIGH];
        rating[HIGH]   |= profit[HIGH]   & drawdown[LOW]    & (lot[LOW] | lot[MEDIUM]);
        rating[MEDIUM] |= profit[HIGH]   & drawdown[LOW]    & lot[HIGH];
        rating[HIGH]   |= profit[HIGH]   & drawdown[MEDIUM] & lot[LOW];
        rating[MEDIUM] |= profit[HIGH]   & drawdown[MEDIUM] & lot[MEDIUM];
        rating[NOT_LOW]|= profit[HIGH]   & drawdown[MEDIUM] & lot[HIGH];
        rating[LOW]    |= profit[HIGH]   & drawdown[HIGH];
     rating[VERY_HIGH] |= profit[HIGHER] & (drawdown[LOW] + drawdown[MEDIUM]) & lot[LOW];
        rating[HIGH]   |= profit[HIGHER] & (drawdown[LOW] + drawdown[MEDIUM]) & lot[MEDIUM];
        rating[MEDIUM] |= profit[HIGHER] & drawdown[LOW]    & lot[HIGH];
        rating[MEDIUM] |= profit[HIGHER] & drawdown[MEDIUM] & lot[HIGH];
        rating[MEDIUM] |= profit[HIGHER] & drawdown[HIGH]   & lot[LOW];
        rating[LOW]    |= profit[HIGHER] & drawdown[HIGH]   & (lot[MEDIUM] + lot[HIGH]);
        rating.defuzzify(1000);
        return rating.Value;
    }

    void testRating()
    {
        double p, dd, l;
        cout << "profit: ";
        cin >> p;
        cout.width(8);
        cout.precision(2);
        cout.setf(ios::right);
        for (int j=0; j<=10; j++)
        {
            l = 0.01 * std::pow(10.0, (double)j * 2.0 / 10.0);
            cout << l << '\t';
        }
        cout << endl;
        for (int i=0; i<=10; i++)
        {
            dd = i * 10;
            cout << dd << '\t';
            for (int j=0; j<=10; j++)
            {
                l = 0.01 * std::pow(10.0, (double)j * 2.0 / 10.0);
                cout << calc(p, dd, l) << '\t';
            }
            cout << endl;
        }
    }

}

int main()
{
    //testFuzzyType();
    //testTerm();
    //testLVar();
    //testFuzzyOne();
    rating::testRating();
    return 0;
}
