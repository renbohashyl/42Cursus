#pragma once

#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

#include <iostream>
#include <string>
#include <exception>

class Form;

class Bureaucrat {
	private:
		const std::string	kName_;
		int	grade_;
		Bureaucrat(const Bureaucrat& copy);
		Bureaucrat& operator=(const Bureaucrat& operland);
	public:
		Bureaucrat();
		Bureaucrat(const std::string setName, const int setGrade);
		~Bureaucrat();

		const std::string& getName() const;
		const int& getGrade() const;
		void increase_grade();
		void decrease_grade();
		void signForm(Form& _form) const;

		class GradeTooHighException : public std::exception {
			public :
				const char *what() const throw() { return ("Grade is Too High"); }
		};
		class GradeTooLowException : public std::exception {
			public :
				const char *what() const throw() { return ("Grade is Too Low"); }
		};
};

std::ostream& operator<< (std::ostream& os, const Bureaucrat& bureaucrat);

#endif