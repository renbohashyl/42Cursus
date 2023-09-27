#include "ScavTrap.hpp"
#include "FragTrap.hpp"

class DiamondTrap : public ScavTrap, public FragTrap {
	private:
		std::string name;
	public:
		DiamondTrap(void);
		DiamondTrap(std::string setName);
		DiamondTrap& operator=(const DiamondTrap& copy_assign);
		void	attack(std::string target);
		void	whoAmI(void);
		~DiamondTrap(void);
};