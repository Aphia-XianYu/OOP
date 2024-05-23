#pragma once
#include<stdexcept>
#include<algorithm>
#include<iostream>
template <class T>
class Vector {
public:
    Vector();                      // creates an empty vector
    Vector(int size);              // creates a vector for holding 'size' elements
    Vector(const Vector& r);       // the copy ctor
    ~Vector();                     // destructs the vector 
    T& operator[](int index);      // accesses the specified element without bounds checking
    T& at(int index);              // accesses the specified element, throws an exception of
    // type 'std::out_of_range' when index <0 or >=m_nSize
    int size() const;              // return the size of the container
    void push_back(const T& x);    // adds an element to the end 
    void clear();                  // clears the contents
    bool empty() const;            // checks whether the container is empty 
	Vector& operator=(const Vector& other);
private:
    void inflate();                // expand the storage of the container to a new capacity,
    // e.g. 2*m_nCapacity
    T* m_pElements;                // pointer to the dynamically allocated storage
    int m_nSize;                   // the number of elements in the container
    int m_nCapacity;               // the total number of elements that can be held in the
    // allocated storage
};
template<class T>
Vector<T>::Vector() :m_pElements(nullptr),m_nSize(0),m_nCapacity(1){
	m_pElements = new T[m_nCapacity];
}
template<class T>
Vector<T>::Vector(int size) {
	m_pElements = new T[size];
	for (int i = 0; i < size; i++)
		m_pElements[i] = T();// initialize each object in Vector
	m_nCapacity = size;
	m_nSize = 0;// it is empty so set it to zero;
}
template<class T>
Vector<T>::Vector(const Vector& r) {
	// Firstly Clear the original object 
	//then re-allocate the memory
	delete[]m_pElements;
	m_pElements = new T[r.m_nCapacity];
	// Copy the contents of a Vector
	std::copy(r.m_pElements, r.m_pElements + r.m_nSize, m_pElements);
	m_nSize = r.m_nSize;
	m_nCapacity = r.m_nCapacity;
}
template<class T>
Vector<T>::~Vector() {
	// free memory
	delete[]m_pElements;
	m_pElements = nullptr;
}
template<class T>
T& Vector<T>::operator[](int index) {
	return m_pElements[index];
}
template<class T>
T& Vector<T>::at(int index) {
	if (index < 0 || index >= m_nSize) {//Check the boundary
		throw std::out_of_range("Index out of range");
	}
	else {
		return m_pElements[index];
	}
}
template<class T>
void Vector<T>::push_back(const T& x) {

	if (m_nSize == m_nCapacity)
		inflate();
	m_pElements[m_nSize++]=x;
}
template<class T>
void Vector<T>::clear() {
	delete[]m_pElements;//free old memory
	m_nSize = 0;
	m_nCapacity = 1;
	m_pElements = new T[m_nCapacity];//allocate new memory
}
template<class T>
bool Vector<T>::empty() const {
	return m_nSize == 0;
}
template<class T>
int Vector<T>::size() const {
	return m_nSize;
}
template<class T>
void Vector<T>::inflate() {
	T* new_Elements = new T[2 * m_nCapacity];//Allocate new memory
	for (int i = 0; i < m_nSize; i++) {
		new_Elements[i] = std::move(m_pElements[i]);//copy from the old Vector
	}
	delete[] m_pElements;//delete old Vector
	m_pElements = new_Elements;
	m_nCapacity = 2 * m_nCapacity;

}
template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
	// Firstly Clear the original object 
	//then re-allocate the memory
	delete[]m_pElements;
	m_pElements = new T[other.m_nCapacity];
	// Copy the contents of a Vector
	std::copy(other.m_pElements, other.m_pElements + other.m_nSize, m_pElements);
	m_nSize = other.m_nSize;
	m_nCapacity = other.m_nCapacity;
	return *this;
}
