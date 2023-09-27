#include "AMateria.hpp"
#include "MateriaSource.hpp"
#include "Cure.hpp"
#include "Ice.hpp"

void	copy_constructor_test()
{
	Character nothing("nothing");
	//this 'nothing' character has no anything, so he's Inv_ has NULL, i mean 0x0
	Character copied(nothing);
}

void	unequip_test()
{
	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());
	ICharacter* me = new Character("me");
	AMateria* tmp;

	tmp = src->createMateria("ice");
	me->equip(tmp);
	me->unequip(0);
	delete tmp;
	tmp = src->createMateria("cure");
	me->equip(tmp);
	me->unequip(0);
	delete tmp;

	delete me;
	delete src;
}

void	basic_test()
{
	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());
	ICharacter* me = new Character("me");
	AMateria* tmp;

	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);
	ICharacter* bob = new Character("bob");
	me->use(0, *bob);
	me->use(1, *bob);

	delete bob;
	delete me;
	delete src;
}

int	main()
{
	basic_test();
	//unequip_test();
	copy_constructor_test();
	system("leaks InterfaceNrecap");
}