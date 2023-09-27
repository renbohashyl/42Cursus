template <typename T>
T min (const T a, const T b) {
	return ( a < b ? a : b );
}

int main() {
	::min(4, 56);
}