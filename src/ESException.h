#ifndef ES_EXCEPTION_HPP
#define ES_EXCEPTION_HPP

#include <string>
#include <exception>

//enum Reason
//{
//    OPEN_ERROR,
//    FATAL_ERROR,
//    BAD_FILE,
//    INVAL_TOKEN,
//    NOT_SUPPORTED,
///*fact*/
//	REASSIGN_INIT,
//
//    PRINT_USAGE,
//    UNKNOWN_ERROR,
//};


class ESException : public std::exception {
public:
//    ESException(const Reason &reason, const std::string &details);
//    ESException(const Reason &reason);

    ESException();
    ESException(const std::string &details);

    ~ESException();
    ESException(const ESException &cpy);

    const char *what() const noexcept;
private:
//    const Reason reason_;
    const std::string details_;

    ESException &operator=(const ESException &rvl) = delete;
};

#endif /*ES_EXCEPTION_HPP*/
