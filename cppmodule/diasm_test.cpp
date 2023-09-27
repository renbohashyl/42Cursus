class A {
	private:
		int a;
	public:
		virtual void four() { this->a = 4; };
		virtual int	getNum() const { return (this->a); };
		A() : a(0) { }
};

class B : public A {
	private:
		int b;
	public:
		void four() { this->b = 44; };
		int	getNum() const { return (this->b); };
		B() : b(0) { }
};

int	main() {
	A *a = new B();
	B *b = static_cast<B*>(new A());
	a->four();
	b->four();
	int bb = a->getNum();
	int aa = b->getNum();
	return (0);
}