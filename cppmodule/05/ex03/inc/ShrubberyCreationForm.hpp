#pragma once

#ifndef SHRUBBERYCREATIONFORM_HPP
# define SHRUBBERYCREATIONFORM_HPP

#include "AForm.hpp"

class ShrubberyCreationForm : public AForm {
	private:
		const std::string kTarget_;
		ShrubberyCreationForm& operator=(const ShrubberyCreationForm& operland);
		ShrubberyCreationForm(const ShrubberyCreationForm& copy);
	public:
		ShrubberyCreationForm(const std::string target);
		~ShrubberyCreationForm();
		virtual void execute(Bureaucrat const& executor) const;
};

#endif