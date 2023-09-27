#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form()
	: kName_("Default_Form"), signableGrade_(150), executableGrade_(150), isSigned_(false) { }

Form::Form(const std::string name, const int signGrade, const int execGrade)
	: kName_(name), signableGrade_(signGrade), executableGrade_(execGrade), isSigned_(false) {
	if (this->signableGrade_ > 150 || this->executableGrade_ > 150) {
		throw(Form::GradeTooLowException());
	} else if (this->signableGrade_ < 1 || this->executableGrade_ < 1) {
		throw(Form::GradeTooHighException());
	}
}

void Form::beSigned(const Bureaucrat& _bureaucrat) {
	if (_bureaucrat.getGrade() > this->get_signableGrade())
		throw(Form::GradeTooLowException());
	this->isSigned_ = this->isSigned_ ^ 1;
}

const std::string& Form::getName() const { return (this->kName_); }
const bool& Form::get_isSigned() const { return (this->isSigned_); }
const int& Form::get_signableGrade() const { return (this->signableGrade_); }
const int& Form::get_executableGrade() const { return (this->executableGrade_); }

Form::~Form() { }

std::ostream& operator<< (std::ostream& os, const Form& form) {
	os << "form name : " << form.getName() << std::endl
	<< "signed : " << form.get_isSigned() << std::endl
	<< "signable grade : " << form.get_signableGrade() << std::endl
	<< "executable grade : " << form.get_executableGrade();
	return (os);
}