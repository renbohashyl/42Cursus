#include "phonebook.hpp"

int	main()
{
	Phonebook book;
	std::string str;

	while ( true )
	{
		std::cout << "usage : [ADD] [SEARCH] [EXIT]\n";
		std::getline(std::cin, str);
		if (str == "ADD")
			book.add();
		else if (str == "SEARCH")
			book.search();
		else if (str == "EXIT")
			exit(0);
		else if (std::cin.eof())
			exit(1);
	}
	return (0);
}