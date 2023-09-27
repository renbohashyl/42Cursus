#include "RobotomyRequestForm.hpp"
#include "Bureaucrat.hpp"
#include <cstdlib>
#include <ctime>

RobotomyRequestForm::RobotomyRequestForm(const std::string target)
	: AForm("RobotomyRequestForm", 72, 45), kTarget_(target) { }

void	RobotomyRequestForm::execute(Bureaucrat const& executor) const {
	if (executor.getGrade() > this->get_executableGrade()) {
		throw(AForm::GradeTooLowException());
	} else if (!this->get_isSigned()) {
		throw(AForm::FormNotSigned());
	} else {
		srand(time(NULL));
		if (rand() % 2) {
			std::cout << this->kTarget_ << " has been robotomized successfully 50\% of the time." << std::endl;
		} else {
			std::cout << "the robotomy failed." << std::endl;
		}
	}
}

RobotomyRequestForm::~RobotomyRequestForm() { }