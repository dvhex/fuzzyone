#ifndef L_VAR_H
#define L_VAR_H

#include "Term.h"
#include <map>

namespace Fuzzy
{

    typedef std::map<int, Term*> TermsMap;
    
    class LVar
    {
        public:
            double Value;
            virtual ~LVar();
            virtual void setTerm(int index, Term *term) {pTerms[index] = term;}
            FuzzyType &operator[](int index);
            const LVar &operator=(double x) {fuzzify(x); return *this;}
            const TermsMap &Terms() const {return pTerms;}
            void zero();
            void fuzzify(double x);
            void defuzzify(unsigned resolution = 1000);
        protected:
            TermsMap pTerms;
        private:
            LVar operator=(const LVar &src);
    };
};

#endif //L_VARH
