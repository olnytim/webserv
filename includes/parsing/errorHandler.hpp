
#ifndef ERRORHANDLER_HPP
#define ERRORHANDLER_HPP
#include "exceptions.hpp"

class errorHandler {
    public:
        static void reportError(const ParseException &ex) {
            throw ex;
        }
};


#endif //ERRORHANDLER_HPP
