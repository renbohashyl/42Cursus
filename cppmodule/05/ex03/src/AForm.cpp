#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm(const std::string name, const int signGrade, const int execGrade)
	: kName_(name), signableGrade_(signGrade), executableGrade_(execGrade), isSigned_(false) {
	if (this->signableGrade_ > 150 || this->executableGrade_ > 150) {
		throw(AForm::GradeTooLowException());
	} else if (this->signableGrade_ < 1 || this->executableGrade_ < 1) {
		throw(AForm::GradeTooHighException());
	}
}

void AForm::beSigned(const Bureaucrat& _bureaucrat) {
	if (_bureaucrat.getGrade() > this->get_signableGrade())
		throw(AForm::GradeTooLowException());
	this->isSigned_ = this->isSigned_ ^ 1;
}

const std::string& AForm::getName() const { return (this->kName_); }
const bool& AForm::get_isSigned() const { return (this->isSigned_); }
const int& AForm::get_signableGrade() const { return (this->signableGrade_); }
const int& AForm::get_executableGrade() const { return (this->executableGrade_); }

AForm::~AForm() { }

std::ostream& operator<< (std::ostream& os, const AForm& AForm) {
	os << "AForm name : " << AForm.getName() << std::endl
	<< "signed : " << AForm.get_isSigned() << std::endl
	<< "signable grade : " << AForm.get_signableGrade() << std::endl
	<< "executable grade : " << AForm.get_executableGrade();
	return (os);
}