#include "phonebook.hpp"

Phonebook::Phonebook() { index = 0; }

Phonebook::~Phonebook() { }

std::string& proc_one_line(std::string& str, const char *type_to_cout)
{
	while (1)
	{
		std::cout << type_to_cout << std::endl;
		std::getline(std::cin, str);
		if (std::cin.eof())
		{
			std::cout << "You've just entered EOF! terminating program because stream buffer cannot be restored\n";
			exit(1);
		}
		else if (str == "")
			std::cout << "------------------------------------\noh come on.. you didn't type anything.... try again\n------------------------------------\n\n";
		else
			break ;
	}
	std::cout << "test : " << str << std::endl;
	return (str);
}

void	Phonebook::add(void)
{
	std::string	str;

	std::cout << "test index : " << this->index << std::endl;
	this->person[this->index % 8].add_first_name(proc_one_line(str, "type first_name :"));
	this->person[this->index % 8].add_last_name(proc_one_line(str, "type last_name :"));
	this->person[this->index % 8].add_nickname(proc_one_line(str, "type nickname :"));
	this->person[this->index % 8].add_phone_number(proc_one_line(str, "type phone_number :"));
	this->person[this->index % 8].add_secret(proc_one_line(str, "your darkest_secret :"));
	(this->index)++;
	std::cout << "test index : " << this->index << std::endl;
}

void	Phonebook::search(void)
{
	int	searching(0);

	while (1)
	{
		std::cout << "[0] : return to first menu | [1 ~ 8] : search for contacts\nsearching index : ";
		std::cin >> searching;
		if (std::cin.fail() || searching < 0 || searching >= 9)
		{
			if (std::cin.eof())
			{
				std::cout << "You've just entered EOF! terminating program because stream buffer cannot be restored\n";
				exit(EXIT_FAILURE);
			}
			std::cout << "------------------------------------\nsomething went wrong, re-enter\n------------------------------------\n";
			std::cin.clear();
			std::cin.ignore(100, '\n');
		}
		else if (searching == 0)
			break ;
		else if (searching > this->index)
			std::cout << "------------------------------------\nthere is no saved content, try again\n------------------------------------\n";
		else
			this->person[searching - 1].print(searching);
	}
	std::cin.ignore(100, '\n');
}
