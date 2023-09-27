#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

#include <string>

class ClapTrap
{
	protected:
		std::string	name;
		unsigned int	hp;
		unsigned int	maxhp;
		unsigned int	mp;
		unsigned int	dmg;
	public:
		ClapTrap(void);
		ClapTrap(const std::string setName);
		ClapTrap(const std::string setName, unsigned int setHP, unsigned int setMP, unsigned int setDMG);
		ClapTrap(const ClapTrap &copy);
		ClapTrap& operator=(const ClapTrap &copy_assign);
		void	attack(const std::string& target);
		void	takeDamage(unsigned int amount);
		void	beRepaired(unsigned int amount);
		int		getAttackDamage(void) const;
		~ClapTrap();
};

#endif