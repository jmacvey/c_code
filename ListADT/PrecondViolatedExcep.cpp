#include 

PrecondViolatedExcep::PrecondViolatedExcep(const std::string& message) 
	: logic_error("Precond Violated Exception: " + message) {

} // end impl