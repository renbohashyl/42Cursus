#include <iostream>

class Contact
{
	private:
		std::string	first_name;
		std::string	last_name;
		std::string	nickname;
		std::string	phone_number;
		std::string	secret;
	public:
		void	add_first_name(std::string& str);
		void	add_last_name(std::string& str);
		void	add_nickname(std::string& str);
		void	add_phone_number(std::string& str);
		void	add_secret(std::string& str);
		void	print(const int index);
};