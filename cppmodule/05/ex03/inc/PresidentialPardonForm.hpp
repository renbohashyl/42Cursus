#pragma once

#ifndef PRESIDENTIALPARDONFORM_HPP
# define PRESIDENTIALPARDONFORM_HPP

#include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
	private:
		const std::string kTarget_;
		PresidentialPardonForm& operator=(const PresidentialPardonForm& operland);
		PresidentialPardonForm(const PresidentialPardonForm& copy);
	public:
		PresidentialPardonForm(const std::string target);
		~PresidentialPardonForm();
		virtual void execute(Bureaucrat const& executor) const;
};

#endif