#include "Weapon.hpp"

class HumanB
{
	private:
		std::string	name;
		Weapon		*weapon;
	public:
		HumanB(std::string setname);
		HumanB(std::string setname, Weapon &setweapon);
		void attack(void) const;
		void setWeapon(Weapon &setWeapon);
		~HumanB(void);
};