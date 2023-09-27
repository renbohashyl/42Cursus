#include "Weapon.hpp"

class HumanA
{
	private:
		std::string	name;
		Weapon		&weapon;
	public:
		HumanA(std::string setname, Weapon &setweapon);
		void	attack(void) const;
		~HumanA(void);
};