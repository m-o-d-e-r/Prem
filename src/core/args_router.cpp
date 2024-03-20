
#include "args_router.h"



Option::Option(__OptionRule* rule)
{
    this->__rule = rule;
}


Option::~Option()
{
    delete this->__rule;
}


std::string Option::getShort() {return std::get<0>(*this->__rule);}


std::string Option::getLong() {return std::get<1>(*this->__rule);}


bool Option::getStatus() {return std::get<2>(*this->__rule);}


bool Option::isBool() {return std::get<3>(*this->__rule);}


std::string Option::getDescription() {return std::get<4>(*this->__rule);}












ArgsRouter::ArgsRouter(/* args */)
{
}

ArgsRouter::~ArgsRouter()
{
}
