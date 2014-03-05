#ifndef					SERIALIZETOOLS_HPP_
# define				SERIALIZETOOLS_HPP_

# include				<fstream>
# include				<iostream>
# include				<ctime>
# include				"Exception.hh"

# define				FILE_SIZE (1024)
# define				SAVE_DIR ("./saves")

class					SerializeTools
{
public:
	template<typename T>
	static void				pushInString(std::string &s, T push)
	{
		size_t				i = 0;

		while (i < sizeof(push))
		{
			s.push_back(reinterpret_cast<char *>(&push)[i]);
			++i;
		}
	}

	template<typename T>
	static T				getFromIFS(std::ifstream &ifs) throw (MyException)
	{
		T					val;

		val = 0;
		ifs.read(reinterpret_cast<char *>(&val), sizeof(val));
		if (!ifs)
			throw (MyException("The map is corrupted."));
		return (val);
	}

	template<typename T>
	static T				getInString(std::string &s) throw (MyException)
	{
		T				val = 0;
		size_t			i = 0;

		val = 0;
		if (sizeof(val) > s.size())
			throw (MyException("out of bounds"));
		while (i < sizeof(val) && i < s.size())
		{
			(reinterpret_cast<char *>(&val))[i] = s[i];
			++i;
		}
		return (val);
	}

	static void				saveInFile(std::string const &buffer) throw (MyException)
	{
		// Do some shit
	}

};

#endif