#include "ClapTrap.hpp"

class ScavTrap : virtual public ClapTrap
{
	public:
		ScavTrap(void);
		ScavTrap(const std::string setName);
		ScavTrap(const std::string setName, unsigned int setHP, unsigned int setMP, unsigned int setDMG);
		ScavTrap(const ScavTrap& copy);
		ScavTrap& operator=(const ScavTrap& copy_assign);
		void	attack(const std::string& target);
		void	takeDamage(unsigned int amount);
		void	beRepaired(unsigned int amount);
		void	guardGate(void);
		~ScavTrap(void);
};