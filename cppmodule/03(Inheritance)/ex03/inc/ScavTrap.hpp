#include "ClapTrap.hpp"

class ScavTrap : virtual public ClapTrap
{
	protected:
		const static int	ScavHp = 100;
		const static int	ScavMp = 50;
		const static int	ScavDmg = 20;
	public:
		ScavTrap(void);
		ScavTrap(std::string setName);
		ScavTrap(std::string setName, unsigned int setHP, unsigned int setMP, unsigned int setDMG);
		ScavTrap(const ScavTrap& copy);
		ScavTrap& operator=(const ScavTrap& copy_assign);
		void	attack(const std::string& target);
		void	takeDamage(unsigned int amount);
		void	beRepaired(unsigned int amount);
		void	guardGate(void);
		~ScavTrap(void);
};