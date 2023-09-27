#pragma once

#ifndef AForm_HPP
# define AForm_HPP

#include <string>
#include <iostream>

class Bureaucrat;

class AForm {
	private:
		const std::string	kName_;
		const int	signableGrade_;
		const int	executableGrade_;
		bool	isSigned_;

		AForm(const AForm& copy);
		AForm& operator=(const AForm& operland);
	public:
		AForm(const std::string name, const int signGrade, const int execGrade);
		virtual ~AForm();
		virtual void execute(Bureaucrat const& executor) const = 0;

		void beSigned(const Bureaucrat& _bureaucrat);
		const std::string& getName() const;
		const bool& get_isSigned() const;
		const int& get_signableGrade() const;
		const int& get_executableGrade() const;

		class GradeTooHighException : public std::exception {
			public :
				const char *what() const throw() { return ("Grade is Too High"); }
		};
		class GradeTooLowException : public std::exception {
			public :
				const char *what() const throw() { return ("Grade is Too Low"); }
		};
		class FormNotSigned : public std::exception {
			public:
				const char *what() const throw() { return ("Form, Not Signed"); }
		};
};

std::ostream& operator<< (std::ostream& os, const AForm& AForm);

#endif