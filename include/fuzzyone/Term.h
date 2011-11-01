#ifndef TERM_H_INCLUDED
#define TERM_H_INCLUDED

#include "Hedge.h"
#include "FuzzyOne.h"

namespace Fuzzy
{
    class LVar;

    //базовый клас термов, поддерживает расчёт значения
    class Term
    {
        protected:
            double X;
        public:
            FuzzyType Value;
            Term() {Value = 0; X = 0;}
            Term(const Term& src) {X = src.X; Value = src.Value;}
            virtual ~Term() {}
            FuzzyType Set(double x) {return Value = Calc(X = x);}
            FuzzyType Get() {return Value;}
            double GetX() {return X;}
            FuzzyType operator()(double x) const {return Calc(x);}
            virtual FuzzyType Calc(double x) const = 0;
            virtual double min() const = 0;
            virtual double max() const = 0;
    };

    //базовый класс для треугольного и подобных термов
    class BaseTerm: public Term
    {
        protected:
            double pA, pB;
        public:
            BaseTerm(double a, double b);
            BaseTerm(const BaseTerm &src): Term(src) {pA = src.pA; pB = src.pB;}
            ~BaseTerm() {}
            void A(double value) {pA = value;}
            double A() const {return pA;}
            void B(double value) {pB = value;}
            double B() const {return pB;}
            double min() const {return pA;}
            double max() const {return pB;}
    };

    //треугольный терм, параметры A, B и C - три точки треугольника
    class TriangularTerm: public BaseTerm
    {
        protected:
            double pC;
        public:
            TriangularTerm(double a, double b, double c);
            TriangularTerm(const TriangularTerm &src): BaseTerm(src), pC(src.pC) {}
            ~TriangularTerm() {}
            void C(double value) {pC = value;}
            double C() const {return pC;}
            FuzzyType Calc(double x) const;
            double max() const {return pC;}
    };

    //терм, уходящий в бесконечность, параметры A, B и Left, границы и куда
    //уходит в бесконечность, влево или вправо
    class ShoulderTerm: public BaseTerm
    {
        protected:
            bool pLeft;
        public:
            ShoulderTerm(double a, double b, bool left = true);
            ShoulderTerm(const ShoulderTerm &src): BaseTerm(src), pLeft(src.pLeft) {}
            ~ShoulderTerm() {};
            void Left(bool left) {pLeft = left;}
            bool Left() const {return pLeft;}
            FuzzyType Calc(double x) const;
    };

    class HedgeTerm: public Term
    {
        protected:
            const Term &pBase;
        public:
            HedgeTerm(const Term &baseTerm): pBase(baseTerm) {}
            ~HedgeTerm() {}
            double min() const {return pBase.min();}
            double max() const {return pBase.max();}
        private:
            HedgeTerm(const HedgeTerm&);
    };

    class SimpleHedgeTerm: public HedgeTerm
    {
        protected:
            Hedge *pHedge;
        public:
            SimpleHedgeTerm(const Term &baseTerm, Hedge *hedge): HedgeTerm(baseTerm), pHedge(hedge) {}
            ~SimpleHedgeTerm() {delete pHedge;}
            FuzzyType Calc(double x) const {return (*pHedge)(pBase.Calc(x));}
    };

};

#endif //TERM_H_INCLUDED
