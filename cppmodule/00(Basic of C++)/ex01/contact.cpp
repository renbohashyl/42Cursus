#include "contact.hpp"
#include <iomanip>

void	Contact::add_first_name(std::string& str) { first_name = str; }
void	Contact::add_last_name(std::string& str) { last_name = str; }
void	Contact::add_nickname(std::string& str) { nickname = str; }
void	Contact::add_phone_number(std::string& str) { phone_number = str; }
void	Contact::add_secret(std::string& str) { secret = str; }

void	print_it(std::string str)
{
	std::cout << "|";
	if (str.length() < 9)
		std::cout << std::setw(10) << str;
	else
	{
		for (int i = 0; i < 9; i++)
		{
			std::cout << str[i];
		}
		std::cout << ".";
	}
	std::cout << "|\n";
}

void	Contact::print(const int index)
{
	std::cout << "============\n";
	std::cout << "|" << std::setw(10) << index << "|" << std::endl;
	print_it(this->first_name);
	print_it(this->last_name);
	print_it(this->nickname);
	print_it(this->phone_number);
	std::cout << "============\n";
}