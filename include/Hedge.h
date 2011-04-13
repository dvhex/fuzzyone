#ifndef HEDGE_H
#define HEDGE_H

#include "FuzzyOne.h"

namespace Fuzzy
{
    class Term;

    class Hedge
    {
        public:
            virtual FuzzyType operator()(const Term *term, double x) const;
            virtual FuzzyType operator()(FuzzyType v) const = 0;
    };

    class HedgeNone: public Hedge
    {
        public:
            FuzzyType operator()(FuzzyType v) const {return v;}
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
