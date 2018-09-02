#include <iostream>
#include "ESException.hpp"

ESException::ESException(const ESException &cpy)
: reason_(cpy.reason_),
  details_(cpy.details_)
{}

ESException::~ESException()
{}

ESException::ESException(const Reason &reason, const std::string &details)
: reason_(reason),
  details_(details)
{}

const char *ESException::what() const noexcept
{
    std::string what;

    switch(reason_)
    {
		case Reason::OPEN_ERROR:      what = "Open error: \e[0m"             ; break;
		case Reason::FATAL_ERROR:     what = "\e[0;31m Fatal error: \e[0m"   ; break;
		case Reason::UNKNOWN_ERROR:
		default:
                                      what = "Unknown error:";
    }
    what += details_;
    return what.c_str();
}
