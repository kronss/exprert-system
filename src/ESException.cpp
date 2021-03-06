#include "ESException.h"

#include <iostream>

#define RED    "\e[0;31m"
#define RESSET "\e[0m"
#define NO_STR ""
//
//ESException::ESException(const ESException &cpy)
//: reason_(cpy.reason_),
//  details_(cpy.details_)
//{}
//
//ESException::~ESException()
//{}
//
//ESException::ESException(const Reason &reason, const std::string &details)
//: reason_(reason),
//  details_(details)
//{}
//
//ESException::ESException(const Reason &reason)
//: reason_(reason),
//  details_(NO_STR)
//{}
//
//const char *ESException::what() const noexcept
//{
//    std::string what;
//
//    switch(reason_)
//    {
//		case Reason::OPEN_ERROR:      what = "Open error: "                 ; break;
//		case Reason::FATAL_ERROR:     what = "Fatal error: "                ; break;
//		case Reason::BAD_FILE:        what = "Bad file: "                   ; break;
//		case Reason::INVAL_TOKEN:     what = "Not supported token: "        ; break;
//		case Reason::NOT_SUPPORTED:   what = "Unsupported token: "          ; break;
//		/*Fact*/
//		case Reason::REASSIGN_INIT:   what = "Trying reassign init fact"    ; break;
//
//		case Reason::PRINT_USAGE:                                           ; break;
//		case Reason::UNKNOWN_ERROR:
//
//		default:
//                                      what = "Unknown error:";
//    }
//    what += details_;
//    return what.c_str();
//}




ESException::ESException(const ESException &cpy)
: runtime_error(cpy.details_), details_(cpy.details_)
{}

ESException::~ESException()
{}

ESException::ESException(const std::string &details)
: runtime_error(details), details_(details)
{}

ESException::ESException()
: runtime_error(NO_STR), details_(NO_STR)
{}

const char *ESException::what() const noexcept
{
	return runtime_error::what();
}

std::ostream & operator << (std::ostream & o, ESException const & )
{
	return o;
}
