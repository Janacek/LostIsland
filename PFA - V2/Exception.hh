#ifndef EXCEPTION_HH_
# define EXCEPTION_HH_

# include		<exception>
# include		<stdexcept>
# include		<string>

class			MyException : public std::runtime_error
{
private:
	const std::string	_name;
public:
	MyException(std::string const &) throw();
	virtual ~MyException() throw();
	virtual const char	*what() const throw();
};

#endif // !EXCEPTION_HH_
