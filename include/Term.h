#ifndef TERM_H_INCLUDED
#define TERM_H_INCLUDED

#include "FuzzyOne.h"

namespace Fuzzy
{
    class LVar;

    //базовый клас теромов, поддерживает расчёт значения
    class Term
    {
        protected:
            FuzzyType pValue;
        public:
            Term() {pValue = 0;}
            virtual ~Term() {}
            virtual FuzzyType Set(FuzzyType x) {return pValue = Calc(x);}
            virtual FuzzyType Get() {return pValue;}
            virtual FuzzyType Calc(FuzzyType x) = 0;
            friend class LVar;
    };

    //треугольный терм, параметры A, B и C - три точки треугольника
    class TriangularTerm: public Term
    {
        private:
            FuzzyType pA, pB, pC;
        public:
            TriangularTerm(FuzzyType a, FuzzyType b, FuzzyType c);
            ~TriangularTerm() {}
            void A(FuzzyType value) {pA = value;}
            FuzzyType A() const {return pA;}
            void B(FuzzyType value) {pB = value;}
            FuzzyType B() const {return pB;}
            void C(FuzzyType value) {pC = value;}
            FuzzyType C() const {return pC;}
            FuzzyType Calc(FuzzyType x);
    };

    //терм, уходящий в бесконечность, параметры A, B и Left, границы и куда
    //уходит в бесконечность, влево или вправо
    class ShoulderTerm: public Term
    {
        private:
            FuzzyType pA, pB;
            bool pLeft;
        public:
            ShoulderTerm(FuzzyType a, FuzzyType b, bool left = true);
            ~ShoulderTerm() {};
            void A(FuzzyType value) {pA = value;}
            FuzzyType A() const {return pA;}
            void B(FuzzyType value) {pB = value;}
            FuzzyType B() const {return pB;}
            void Left(bool left) {pLeft = left;}
            bool Left() const {return pLeft;}
            FuzzyType Calc(FuzzyType x);
    };

};

#endif //TERM_H_INCLUDED
