#include "LoadException.h"

LoadException::LoadException(){ 
	LoadException(""); 
}
LoadException::LoadException(const std::string& message){ 
	this->message_ = message_; 
}

const char* LoadException::what() const throw() {
	return message_.c_str();
}