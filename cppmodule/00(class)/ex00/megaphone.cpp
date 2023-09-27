#include <iostream>

int	main(const int ac, const char **av)
{
	if (ac == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return (0);
	}

	for (int i = 1; av[i]; i++)
	{
		for (int j = 0; av[i][j]; j++)
		{
			std::cout << static_cast<char>(std::toupper(av[i][j]));
		}
	}
	std::cout << std::endl;
	return (0);
}