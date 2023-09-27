#include <iostream>
#include <fstream>
#include <string>

void	check_line_and_write_it(std::string &line, std::string s1, std::string s2)
{
	size_t	s1_pos(line.find(s1));

	if (s1_pos != std::string::npos) {
		line.erase(s1_pos, s1.length());
		line.insert(s1_pos, s2);
	}
}

int	main(const int cnt, const char **av)
{
	if (cnt != 4)
		return (1);
	std::string	line(av[1]);
	std::ifstream infile(av[1]);
	if (infile.is_open()) {
		std::ofstream outfile(line.append(".replace"));
		while (getline(infile, line)) {
			check_line_and_write_it(line, av[2], av[3]);
			outfile << line << std::endl;
		}
	}
	return (0);
}