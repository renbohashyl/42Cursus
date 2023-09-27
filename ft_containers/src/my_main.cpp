#include <iostream>

#ifdef _use_std
 #include <vector>
 #include <stack>
 #include <map>
 #include <set>
 using namespace std;
#else
 #include "vector.hpp"
 #include "stack.hpp"
 #include "map.hpp"
 #include "set.hpp"
 using namespace ft;
#endif

void	test()
{
	#define ACAP 3
	#define SCAP 10

	map<int, int> a;
	try
	{
		for (int i = 0; i < 10; i++)
			a.insert(pair<int, char>(i + 1, (i + 1) * 3));
		a.erase(++a.begin());
		a.erase(a.begin());
		map<int, int>::iterator it;
		it = a.upper_bound(11);
	}
	catch (...)
	{
		std::cerr << "Dang!!!" << std::endl;
	}
}

int	main()
{
	test();
	//system("leaks ft_containers");
	system("leaks ft_containers | grep \"leaks for\"");
	return (0);
}