#include "Character.hpp"
#include <iostream>

////////////////////////////////
/* the original of this class */
////////////////////////////////
Character::Character() : Name_("Player") {
	for (int i = 0; i < 4; i++) {
		Inv_[i] = NULL;
	}
}
Character::Character(const std::string& name) : Name_(name) {
	for (int i = 0; i < 4; i++) {
		Inv_[i] = NULL;
	}
}

Character::Character(const Character& copy) : Name_(copy.getName()) {
	for (int i = 0; i < 4; i++) {
		this->Inv_[i] = NULL;
		if (copy.Inv_[i])
			this->Inv_[i] = copy.Inv_[i]->clone();
	}
}

Character& Character::operator=(const Character& operland) {
	if (this != &operland) {
		this->Name_ = operland.Name_;
		for (int i = 0; i < 4; i++) {
			if (this->Inv_[i])
				delete (this->Inv_[i]);
			this->Inv_[i] = NULL;
			if (operland.Inv_[i]) {
				this->Inv_[i] = operland.Inv_[i]->clone();
			}
		}
	}
	return (*this);
}

Character::~Character() {
	for (int i = 0; i < 4; i++) {
		if (this->Inv_[i])
			delete (this->Inv_[i]);
		this->Inv_[i] = NULL;
	}
}
////////////////////////////////
/* the original of this class */
////////////////////////////////


//////////////////////////////
/* the interface implements */
//////////////////////////////

void	Character::equip(AMateria* m) {
	for (int i = 0; i < 4; i++) {
		if (this->Inv_[i] == NULL) {
			this->Inv_[i] = m;
			break ;
		}
	}
}

void	Character::unequip(int idx) {
	if (idx >= 0 && idx < 4 && this->Inv_[idx] != NULL)
		this->Inv_[idx] = NULL;
}

void	Character::use(int idx, ICharacter& target) {
	if (idx >= 0 && idx < 4 && this->Inv_[idx] != NULL)
		this->Inv_[idx]->use(target);
}

std::string	const& Character::getName() const { return (this->Name_); }