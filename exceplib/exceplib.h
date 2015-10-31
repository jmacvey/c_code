#ifndef _PRECOND_VIOLATED_EXCEP
#define _PRECOND_VIOLATED_EXCEP

#include <stdexcept>
#include <string>

class PrecondViolatedExcep : public std::logic_error{
public:
	PrecondViolatedExcep(const std::string& message);
};// end exception

class NotFoundException : public std::logic_error{
public:
	NotFoundException(const std::string& message);
};

#endif