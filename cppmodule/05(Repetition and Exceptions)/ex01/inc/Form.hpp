#pragma once

#ifndef FORM_HPP
# define FORM_HPP

#include <string>
#include <iostream>

class Bureaucrat;

class Form {
	private:
		const std::string	kName_;
		const int	signableGrade_;
		const int	executableGrade_;
		bool	isSigned_;

		Form(const Form& copy);
		Form& operator=(const Form& operland);
	public:
		Form();
		Form(const std::string name, const int signGrade, const int execGrade);
		~Form();

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
};

std::ostream& operator<< (std::ostream& os, const Form& form);

#endif