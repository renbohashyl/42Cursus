#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm(const std::string target)
	: AForm("ShrubberyCreationForm", 145, 137), kTarget_(target) { }

void ShrubberyCreationForm::execute(Bureaucrat const& executor) const {
	if (executor.getGrade() > this->get_executableGrade()) {
		throw(AForm::GradeTooLowException());
	} else if (!this->get_isSigned()) {
		throw(AForm::FormNotSigned());
	} else {
		std::ifstream tree("tree.txt");
		std::string temp_str(this->kTarget_);
		temp_str.append("_ShrubberyCreationForm");
		std::ofstream outfile(temp_str.c_str());
		std::cout << "the file : " << temp_str;
		if (tree.is_open()) {
			while (getline(tree, temp_str))
				outfile << temp_str << std::endl;
		}
		std::cout << " has been created" << std::endl;
	}
}

ShrubberyCreationForm::~ShrubberyCreationForm() { }