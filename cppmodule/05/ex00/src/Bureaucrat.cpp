#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : kName_("Default Bureaucrat"), grade_(150) { }
Bureaucrat::Bureaucrat(const std::string setName, const int setGrade)
	: kName_(setName) {
	if (setGrade > 150) {
		throw (Bureaucrat::GradeTooLowException());
	} else if (setGrade < 1) {
		throw (Bureaucrat::GradeTooHighException());
	}
	this->grade_ = setGrade;
}

const std::string& Bureaucrat::getName() const { return (this->kName_); }
const int& Bureaucrat::getGrade() const { return (this->grade_); }

void	Bureaucrat::increase_grade() {
	if (this->grade_ == 1) {
		throw(Bureaucrat::GradeTooHighException());
	}
	(this->grade_)--;
}

void	Bureaucrat::decrease_grade() {
	if (this->grade_ == 150) {
		throw(Bureaucrat::GradeTooLowException());
	}
	(this->grade_)++;
}

Bureaucrat::~Bureaucrat() { }

std::ostream& operator<< (std::ostream& os, const Bureaucrat& bureaucrat) {
	os << bureaucrat.getName() << ", Bureaucrat grade " << bureaucrat.getGrade();
	return (os);
}