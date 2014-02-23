#include "pointerException.hpp"

PointerException::PointerException(){
    this->mText = "there was a NULL-pointer. no idea where ...";
}

PointerException::PointerException(std::string functionName){
    this->mText = "in function " + functionName + " there was a NULL-pointer";
}

PointerException::PointerException(std::string functionName, std::string variableName){
    this->mText = "in function " + functionName + " the pointer " + variableName + " was NULL";
}
