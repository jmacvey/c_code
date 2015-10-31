#include "exceplib.h"

PrecondViolatedExcep::PrecondViolatedExcep(const std::string& message)
	: logic_error("Precond Violated Exception: " + message) {

} // end impl

NotFoundException::NotFoundException(const std::string& message) 
	: logic_error("NotFoundException: " + message) {
} // end impl
