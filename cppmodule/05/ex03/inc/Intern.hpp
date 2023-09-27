#include <string>

class AForm;

class Intern {
	private:
		Intern(const Intern& copy);
		Intern& operator=(const Intern& operland);
	public:
		Intern();
		AForm* makeForm(const std::string form_name, const std::string target);
		class ItDoesNotExist : public std::exception {
			public:
				const char *what() const throw() { return ("That form name doesn't exist"); }
		};
		~Intern();
};