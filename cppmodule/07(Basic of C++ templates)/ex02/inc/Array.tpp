template <typename T>
Array<T>::Array() {
	this->data_ = new T[0];
	this->m_size_ = 0;
}

template <typename T>
Array<T>::Array( const unsigned int alloc_size ) {
	try {
		this->data_ = new T[alloc_size];
		for (unsigned int i = 0; i < alloc_size; i++) {
			this->data_[i] = 0; 
		}
		this->m_size_ = alloc_size;
	}
	catch (std::exception & e) {
		throw (Array<T>::AccessDenied());
	}
}

template <typename T>
Array<T>::Array( const Array<T>& that ) {
	unsigned int temp_size = that.size();

	this->data_ = new T(temp_size);
	for (unsigned int i = 0; i < temp_size; i++) {
		this->data_[i] = that.data_[i];
	}
	this->m_size_ = temp_size;
}

template <typename T>
Array<T>& Array<T>::operator= ( const Array<T>& rhs ) {
	if (this == &rhs)
		return ;

	delete[] (this->data_);
	this->data_ = new T(rhs.size());
	for (unsigned int i = 0; i < rhs.size(); i++) {
		this->data_[i] = rhs.data_[i];
	}
	return (*this);
}

template <typename T>
T& Array<T>::operator[] ( const unsigned int index ) {
	if (index >= this->size())
		throw (Array::OutOfBound());
	return (this->data_[index]);
}

template <typename T>
const T& Array<T>::operator[] ( const unsigned int index ) const {
	if (index >= this->size())
		throw (Array::OutOfBound());
	return (this->data_[index]);
}

template <typename T>
Array<T>::~Array() {
	delete[] (this->data_);
}

template <typename T>
unsigned int Array<T>::size() const { return (this->m_size_); }