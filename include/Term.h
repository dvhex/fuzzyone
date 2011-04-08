#ifndef TERM_H_INCLUDED
#define TERM_H_INCLUDED

namespace Fuzzy
{

    //базовый клас теромов, поддерживает расчёт значения
    class Term
    {
        public:
            virtual ~Term() {};
            virtual FuzzyType Get(FuzzyType x) = 0;
        private:
    };

    //треугольный терм, параметры A, B и C - три точки треугольника
    class TriangularTerm: public Term
    {
        private:
            FuzzyType pA, pB, pC;
        public:
            TriangularTerm(FuzzyType a, FuzzyType b, FuzzyType c);
            ~TriangularTerm() {}
            FuzzyType Get(FuzzyType x);
            void A(FuzzyType value) {pA = value;}
            FuzzyType A() const {return pA;}
            void B(FuzzyType value) {pB = value;}
            FuzzyType B() const {return pB;}
            void C(FuzzyType value) {pC = value;}
            FuzzyType C() const {return pC;}
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
            FuzzyType Get(FuzzyType x);
            void A(FuzzyType value) {pA = value;}
            FuzzyType A() const {return pA;}
            void B(FuzzyType value) {pB = value;}
            FuzzyType B() const {return pB;}
            void Left(bool left) {pLeft = left;}
            bool Left() const {return pLeft;}
    }

}

#endif //TERM_H_INCLUDED
