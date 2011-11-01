#ifndef FUZZY_ONE_EXCEPT_H
#define FUZZY_ONE_EXCEPT_H

#include <exception>
#include <string>

namespace Fuzzy
{

    class Exception: std::exception
    {
        public:
            Exception(const std::string &mes) throw() {message = mes;}
            Exception(const char *mes) throw() {message = mes;}
            ~Exception() throw() {}
            const char *what() const throw() {return message.c_str();}
        private:
            std::string message;
    };

};

#endif //FUZZY_ONE_EXCEPT_H
