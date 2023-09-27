template <typename Num>
void swap(Num& a, Num& b) {
	Num temp(a);

	a = b;
	b = temp;
}

template <typename AnyType>
AnyType min(AnyType & a, AnyType & b) {
	return (a < b ? a : b);
}

template <typename AnyType>
const AnyType min(const AnyType & a, const AnyType & b) {
	return (a < b ? a : b);
}

template <typename AnyType>
AnyType max(AnyType & a, AnyType & b) {
	return (a > b ? a : b);
}

template <typename AnyType>
const AnyType max(const AnyType & a, const AnyType & b) {
	return (a > b ? a : b);
}