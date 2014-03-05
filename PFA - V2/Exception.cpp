#include		"Exception.hh"

MyException::MyException(std::string const & name) throw() : std::runtime_error(name), _name(name)
{
}

MyException::~MyException() throw()
{
};

const char		*MyException::what() const throw()
{
	return (_name.c_str());
}
