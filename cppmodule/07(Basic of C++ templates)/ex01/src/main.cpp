#include "iter.hpp"
#include <string>

typedef std::string t_type;

enum e_status { e_range = 5 };

int main() {
	t_type tArray[e_range] = {"0", "1", "2", "3", "4"};
	iter(tArray, e_range, example);
	iter(tArray, e_range, print);
	return (0);
}