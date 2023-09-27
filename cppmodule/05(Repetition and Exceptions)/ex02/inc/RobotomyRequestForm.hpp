#include "AForm.hpp"

class RobotomyRequestForm : public AForm {
	private:
		const std::string kTarget_;
		RobotomyRequestForm& operator=(const RobotomyRequestForm& operland);
		RobotomyRequestForm(const RobotomyRequestForm& copy);
	public:
		RobotomyRequestForm(const std::string target);
		~RobotomyRequestForm();
		virtual void execute(Bureaucrat const& executor) const;
};