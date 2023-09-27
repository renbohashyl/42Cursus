#ifndef	WEAPON_HPP
# define WEAPON_HPP

#include <string>

class	Weapon
{
	private :
		std::string name;
	public :
		Weapon(void);
		Weapon(std::string weaponname);
		std::string	&getType(void);
		void	setType(std::string weaponname);
		~Weapon(void);
};

#endif