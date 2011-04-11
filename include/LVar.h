#ifndef L_VAR_H
#define L_VAR_H

#include "Term.h"
#include <map>

namespace Fuzzy
{

    /*
     * TODO: возможно следует всё объединить в один класс
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
