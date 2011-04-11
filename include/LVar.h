#ifndef L_VAR_H
#define L_VAR_H

#include "Term.h"
#include <map>

namespace Fuzzy
{

    /*
     * Краткое описание будущих действий:
     *
     * класс LVar определяет базовые операции над входными и выходными
     * величинами;
     *
     * setTerm должен добавит терм в коллекцию;
     *
     * operator[] должен позволять менять и узнавать величины термов,
     * Можно вместо int сделать string с названием терма;
     *
     * класс InputLVar помимо того поддерживает присваивание действительного
     * числа, при этом все термы пересчитываются;
     *
     * класс OutputLVar должен поддерживать обновление своих значений,
     * возможно, через operator+=.
     *
     * Также в дальнейшем все классы должны поддерживать модификаторы. Сами
     * модификаторы тоже должны быть реализованы в виде классов.
     */
    typedef std::map<int, Term*> TermsMap;
    
    class LVar
    {
        public:
            double Value;
            virtual ~LVar();
            virtual void setTerm(int index, Term *term) {pTerms[index] = term;}
            FuzzyType &operator[](int index);
            const TermsMap &Terms() const {return pTerms;}
            void zero();
            void defuzzify();
        protected:
            TermsMap pTerms;
        private:
            InputLVar operator=(const InputLVar &src);
    };

    class InputLVar: public LVar
    {
        public:
            const InputLVar &operator=(double x) {fuzzify(x); return *this;}
            void fuzzify(double x);
    };

    class OutputLVar: public LVar
    {
        public:
            FuzzyType deFuzzify();
    };
};

#endif //L_VARH
