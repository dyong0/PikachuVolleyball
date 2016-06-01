#include <string>
#include <exception>

class LoadException : public std::exception {
private:
	std::string message_;
public:
	LoadException();
	LoadException(const std::string& message);
	virtual const char* what() const throw();
};