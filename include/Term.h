#ifndef TERM_H_INCLUDED
#define TERM_H_INCLUDED

#include "FuzzyOne.h"

namespace Fuzzy
{
    class LVar;

    //базовый клас термов, поддерживает расчёт значения
    class Term
    {
        public:
            FuzzyType Value;
            Term() {Value = 0;}
            virtual ~Term() {}
            FuzzyType Set(double x) {return Value = Calc(x);}
            FuzzyType Get() {return Value;}
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
        private:
            bool pLeft;
        public:
            ShoulderTerm(double a, double b, bool left = true);
            ~ShoulderTerm() {};
            void Left(bool left) {pLeft = left;}
            bool Left() const {return pLeft;}
            FuzzyType Calc(double x) const;
    };

};

#endif //TERM_H_INCLUDED
