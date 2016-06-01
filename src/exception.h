#include <exception>

class NotRegisteredViewException : public std::exception{
	virtual char const* what() const throw(){
		return "NotRegisteredViewException";
	}
};

class PlayerNotCreated : public std::exception{
	virtual char const* what() const throw(){
		return "PlayerNotCreated";
	}
};