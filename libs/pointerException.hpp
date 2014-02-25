/**
 * class to manage pointer violations
 *
 */

#ifndef LIBS_POINTEREXCEPTION_HPP
#define LIBS_POINTEREXCEPTION_HPP

#include <string>
#include <iostream>

class PointerException {
private:
    std::string mText;
public:
    PointerException();
    PointerException(std::string functionName);
    PointerException(std::string functionName, std::string variableName);
    std::string getString() {return mText;};
};

#endif // LIBS_POINTEREXCEPTION_HPP
