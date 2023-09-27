#include "contact.hpp"
#include <string>

class Phonebook
{
	private:
		Contact person[8];
		int		index;
	public:
		Phonebook();
		void add(void);
		void search(void);
		void show(void);
		~Phonebook();
};
