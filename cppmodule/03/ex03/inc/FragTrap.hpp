#include "ClapTrap.hpp"

class FragTrap : virtual public ClapTrap {
	protected:
		const static int	FragHp = 100;
		const static int	FragMp = 100;
		const static int	FragDmg = 30;
	public :
		FragTrap(void);
		FragTrap(std::string setName);
		FragTrap(std::string setName, unsigned int setHP, unsigned int setMP, unsigned int setDMG);
		FragTrap(FragTrap &copy);
		FragTrap& operator=(FragTrap &copy_assign);
		void	highFivesGuys(void);
		~FragTrap(void);
};