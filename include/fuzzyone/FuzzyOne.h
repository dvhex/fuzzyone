#ifndef FUZZYONE_H
#define FUZZYONE_H

#include <iostream>
#include <map>

/*
 * В этом файле нужно реализовать движок для операций с лингвистическими
 * переменными. Он должен поддерживать различные алгоритмы деффузификации и
 * прочее.
 */

namespace Fuzzy
{
    class LVar;

    typedef std::map<int,LVar*> LVarMap;

    typedef void (*Rule)(LVar*, LVarMap&);

    class FuzzyOne
    {
        public:
            FuzzyOne();
            virtual ~FuzzyOne();
            void setOutputLVar(LVar *var) {pOutLVar = var;}
            //TODO: сделать несколько выходов
            void setInputLVar(int index, LVar *var) {pLVars[index] = var;}
            LVar *operator[](int index) {return pLVars[index];}
            const LVar *out() const {return pOutLVar;}
            void setRule(Rule rule) {pRule = rule;}
            void run();
        protected:
            Rule pRule;
            LVar* pOutLVar;
            LVarMap pLVars;
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
