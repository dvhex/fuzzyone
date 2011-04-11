#ifndef HEDGE_H
#define HEDGE_H

#include "FuzzyOne.h"
#include "Term.h"

namespace Fuzzy
{
    class Hedge
    {
        public:
            virtual FuzzyType operator()(const Term *term, double x) const {return operator()(term->Calc(x));}
            virtual FuzzyType operator()(FuzzyType v) const = 0;
    };

    class HedgeNot: public Hedge
    {
        public:
            FuzzyType operator()(FuzzyType v) const {return ~v;}
    };

    class HedgeVery: public Hedge
    {
        public:
            FuzzyType operator()(FuzzyType v) const;
    };

    class HedgeSomewat: public Hedge
    {
        public:
            FuzzyType operator()(FuzzyType v) const;
    };

    class HedgeAny: public Hedge
    {
        public:
            FuzzyType operator()(FuzzyType v) const;
    };
}

#endif //HEDGE_H
