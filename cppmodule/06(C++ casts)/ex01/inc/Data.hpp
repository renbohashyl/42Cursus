#include <iostream>

typedef struct s_Data
{
	int i;
	float f;
	double d;
} Data;

uintptr_t serialize(Data* ptr);
Data *deserialize(uintptr_t raw);
std::ostream& operator<< (std::ostream& os, const Data& ptr);