#ifndef FUZZYONE_H
#define FUZZYONE_H

#include <iostream>

/*
 * В этом файле нужно реализовать движок для операций с
 * лингвистическими переменными. Он должен поддерживать различные алгоритмы
 * деффузификации и прочее.
 */

namespace Fuzzy
{

    class FuzzyOne
    {
        public:
            FuzzyOne();
            virtual ~FuzzyOne();
        protected:
        private:
    };

    class FuzzyType
    {
        private:
            double v;
        public:
            FuzzyType(): v(0) {}
            FuzzyType(const FuzzyType &src): v(src.v) {}
            FuzzyType(double arg);
            FuzzyType &operator+=(FuzzyType arg);
            FuzzyType &operator-=(FuzzyType arg);
            FuzzyType &operator*=(FuzzyType arg);
            FuzzyType &operator&=(FuzzyType arg);
            FuzzyType &operator|=(FuzzyType arg);
            FuzzyType operator~() const;
            FuzzyType operator+(FuzzyType arg) const;
            FuzzyType operator-(FuzzyType arg) const;
            FuzzyType operator*(FuzzyType arg) const;
            FuzzyType operator&(FuzzyType arg) const;
            FuzzyType operator|(FuzzyType arg) const;
            FuzzyType value() const {return v;}
            operator double() const {return v;}
            friend std::ostream &operator<<(std::ostream &os, FuzzyType arg) {return os << arg.v;}
    };

};

#endif // FUZZYONE_H
