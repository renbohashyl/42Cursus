#pragma once

#ifndef CHARACTER_HPP
# define CHARACTER_HPP

#include "ICharacter.hpp"
#include "AMateria.hpp"

class Character : public ICharacter {
	private:
		std::string	Name_;
		AMateria	*Inv_[4];
	public:
		Character();
		Character(const std::string& name);
		Character(const Character& copy);
		Character& operator=(const Character& operland);
		~Character();
		
		std::string const&	getName() const;
		void	equip(AMateria* m);
		void	unequip(int idx);
		void	use(int idx, ICharacter& target);
};

#endif