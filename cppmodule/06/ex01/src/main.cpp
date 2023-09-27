#include "Data.hpp"

std::ostream& operator<< (std::ostream& os, const Data& data_ptr) {
	os << "data ptr.i <int> : " << data_ptr.i << std::endl \
	<< "data ptr.d <double> : " << data_ptr.d << std::endl \
	<< "data ptr.f <float> : " << data_ptr.f;

	return (os); 
}

uintptr_t serialize(Data* ptr) {
	return (reinterpret_cast<uintptr_t>(ptr));
}

Data *deserialize(uintptr_t raw) {
	return (reinterpret_cast<Data *>(raw));
}

// void check_are_address_same(const Data& data_ptr, const uintptr_t raw_address) {
// 	std::cout << (unsigned long long)&data_ptr << std::endl;
// 	std::cout << raw_address << std::endl;
// 	std::cout << "are they same value? " << \
// 	((unsigned long long)(&data_ptr) == (unsigned long long)raw_address ? "yes" : "no") << std::endl;
// 	std::cout << std::endl;
// }

void check_deserialize(uintptr_t raw_temp) {
	Data *temp(NULL);

	temp = deserialize(raw_temp);
	//check_are_addresses_same(temp, raw_temp);
	std::cout << *temp << std::endl;
	temp->i = 555;
	temp->d = 5.3f;
	temp->f = 0.1f;
}

int	main() {
	Data data_temp;

	data_temp.i = 1;
	data_temp.f = 1.5f;
	data_temp.d = 3.4f;
	uintptr_t raw_temp(serialize(&data_temp));
	// check_are_addresses_same(data_temp, raw_temp);
	check_deserialize(raw_temp);
	std::cout << data_temp << std::endl;
}