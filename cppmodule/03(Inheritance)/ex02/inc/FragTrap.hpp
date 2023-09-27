#include "ClapTrap.hpp"

class FragTrap : public ClapTrap {
	public :
		FragTrap(void);
		FragTrap(const std::string setName);
		FragTrap(const std::string setName, unsigned int setHP, unsigned int setMP, unsigned int setDMG);
		FragTrap(FragTrap &copy);
		FragTrap& operator=(FragTrap &copy_assign);
		void	highFivesGuys(void);
		~FragTrap(void);
};