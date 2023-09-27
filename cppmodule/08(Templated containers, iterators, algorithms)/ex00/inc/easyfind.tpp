class NotFound : public std::exception {
	public:
		const char * what() const throw() { return ("404 Not Found"); };
};

template <typename T>
typename T::iterator	easyfind( T & haystack, int needle ) {
	typename T::iterator	easy(std::find(haystack.begin(), haystack.end(), needle));

	if (easy == haystack.end())
		throw (NotFound());
	return (easy);
}

template <typename T>
const typename T::iterator	easyfind( const T & haystack, const int needle ) {
	const typename T::iterator	easy(std::find(haystack.begin(), haystack.end(), needle));

	if (easy == haystack.end())
		throw (NotFound());
	return (easy);
}