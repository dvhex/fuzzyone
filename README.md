fuzzyone
========

Fast fuzzy logic library

Sorry for my english. I'll tell about this library.

This library may be used for fast resolving tasks of fuzzy logic.
It based on natively C++ language operators, for example, +-*&|= that redefined for using in fuzzy logic.

======
Using:
======

In common case input and output values of type LVar (fuzzy variables) is maden. All values are defined terms using method setTerm. Using of terms is done with index operator with integer value. Then operations is used that based on fuzzy rules, they are written on c++ language but not fuzzy logic language. For example, there are two input values - "first" and "second" and one output value - "result". All values have three terms: LOW = 0, MEDIUM = 1, HIGH = 2. Then we can write this expression:

"If first is LOW and second is MEDIUM, then result is LOW"

as

result[LOW] |= first[LOW] & second[MEDIUM].

For defuzzification you must use method defuzzify(int) that receive value - count of defuzzification intervals.
