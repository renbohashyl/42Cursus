#include "PresidentialPardonForm.hpp"
#include "Bureaucrat.hpp"

PresidentialPardonForm::PresidentialPardonForm(const std::string target)
	: AForm("PresidentialPardonForm", 25, 5), kTarget_(target) { }

void PresidentialPardonForm::execute(Bureaucrat const& executor) const {
	if (executor.getGrade() > this->get_executableGrade()) {
		throw(AForm::GradeTooLowException());
	} else if (!this->get_isSigned()) {
		throw(AForm::FormNotSigned());
	} else {
		std::cout << this->kTarget_ << " has been pardoned by Zaphod Beeblebrox." << std::endl;
	}
}

PresidentialPardonForm::~PresidentialPardonForm() { }