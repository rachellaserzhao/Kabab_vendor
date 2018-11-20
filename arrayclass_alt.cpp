// file:        arrayclass.cpp
// author:      Geoff T
// date:        2017-10-13
// description: implementation of a dynamic array class for CPSC 221 PA2

#ifdef _ARRAYCLASS_H_

// default constructor
// Creates an empty ArrayClass with DEFAULTCAPACITY
template <typename T>
ArrayClass<T>::ArrayClass()
{
	_capacity = DEFAULTCAPACITY;
	_size = 0;
	arr = new T[_capacity];
}

// parameterized constructor
// Creates an empty ArrayClass with capacity of n
template <typename T>
ArrayClass<T>::ArrayClass(unsigned int n)
{
	_capacity = n;
	_size = 0;
	arr = new T[n];
}

// copy constructor
// Creates an ArrayClass as a deep copy of the parameter
template <typename T>
ArrayClass<T>::ArrayClass(const ArrayClass& ac)
{
	copyArray(ac);
	
}

// destructor
template <typename T>
ArrayClass<T>::~ArrayClass()
{
	delete[] arr;
	arr = NULL;
}

// overloaded assignment operator
template <typename T>
ArrayClass<T>& ArrayClass<T>::operator=(const ArrayClass& ac)
{
  
  copyArray(ac);
   
  // The following is stub code only.
  // Please replace with your own implementation
  return *this;
}

////////////////////////
// capacity functions //
////////////////////////

// Returns the number of elements stored in the array
template <typename T>
unsigned int ArrayClass<T>::size() const
{
  return _size;
}

// Returns the maximum capacity of the array
template <typename T>
unsigned int ArrayClass<T>::capacity() const
{
  return _capacity;
}

// Resizes the array
// If n is smaller than the size, then only the
//   first n elements are copied to the new array
template <typename T>
void ArrayClass<T>::resize(unsigned int n)
{
	T* temp = new T[n];
	for (int i = 0; i < n; i++) {
		temp[i] = arr[i];
	}

	delete[] arr;
	arr = temp;
	_size = n;
	_capacity = n;
}

// Check if array is empty
// return true if array is empty
template <typename T>
bool ArrayClass<T>::empty() const
{
  return (_size==0);
}

// Resizes the array to fit exactly as many items
//   as are stored in the array
template <typename T>
void ArrayClass<T>::shrinkToFit()
{
	_capacity = _size;
  	T* temp = new T[_size];
	for (int i = 0; i < _size; i++) 
		temp[i] = arr[i];

	delete[] arr;
	arr = temp;
	
}

//////////////////////////////
// element access functions //
//////////////////////////////

// Returns a reference to the element at position i
//   in the array.
// Throws an out_of_range exception if i is outside
//   the bounds of valid elements
template <typename T>
T& ArrayClass<T>::operator[](unsigned int i)
{
  if (i >= _size) 
	  throw std::out_of_range("i outside valid elements");
 
  return arr[i];
}

// Returns a reference to the element at position i
//   in the array.
// Throws an out_of_range exception if i is outside
//   the bounds of valid elements
template <typename T>
T& ArrayClass<T>::at(unsigned int i)
{
  if (i >= _size) 
	  throw std::out_of_range("i outside valid elements");
  
  return arr[i];
}

// Returns a reference to the first element in the array
// Calling this on an empty array throws out_of_range exception
template <typename T>
T& ArrayClass<T>::front()
{
  if (_size == 0)
	  throw std::out_of_range("can't return front of empty array");
  
  return arr[0];
}

// Returns a reference to the last element in the array
// Calling this on an empty array throws out_of_range exception
template <typename T>
T& ArrayClass<T>::back()
{
  if (_size == 0)
	  throw std::out_of_range("can't return back of empty array");
  
  return arr[(_size-1)];
}

//////////////////////
// modify functions //
//////////////////////

// Add an element at the end
// If array is at capacity before adding, then
//   expand the array to double its capacity and
//   then add.
template <typename T>
void ArrayClass<T>::pushBack(const T& item)
{	if (_size == _capacity)	{
		expandArray();
	}
	arr[_size] = item;
	_size = _size +  1;

}
// Removes the last stored element in the array,
//   reducing container size by 1.
// No effect if called on an empty container
template <typename T>
void ArrayClass<T>::popBack()
{
	if (!(_size == 0)) {
		_size -= 1;
		
	}
}

// Inserts an element before the element at specified position
// Expands the array if necessary
// Elements to the right of position (inclusive) must be shifted
// Throws out_of_range if position is > _size
// POST: item is at position, all elements formerly at position and beyond are shifted
template <typename T>
void ArrayClass<T>::insert(unsigned int position, const T& item)
{
	if (position > _size) 
		throw std::out_of_range("cannot insert at position greater than size of array");


	if (_size == _capacity) {
		expandArray();
	}

	for (unsigned int i = (_size - 1); i > (position-1); i--) { 
		arr[i+1] = arr[i];
	}
	

	arr[position] = item;
	_size = _size + 1;
 }

// Removes an element from the array at specified position.
// Elements to the right of position will be shifted over to fill the gap
// Throws out_of_range if position is >= _size
template <typename T>
void ArrayClass<T>::erase(unsigned int position)
{
  	if (position >= _size) 
		throw std::out_of_range("cannot erase at position greater than size of array");
	
	for (int i = position; i < (_size-1); i++) 
		arr[i] = arr[i+1];
	
	_size -= 1;

}

// Reallocates stored items into a new array of the same size,
//   starting from specified position
// No effect if position is 0 or >= _size
// e.g. startFrom(3) on {1, 2, 3, 4, 5, 6, 7}
//   produces {4, 5, 6, 7, 1, 2, 3}
template <typename T>
void ArrayClass<T>::startFrom(unsigned int position)
{
	if (!((position == 0) || (position >= _size))) {
		T* temp = new T[_capacity];
		int pos = 0;
		for (int i = position; i < _size; i++) {
			temp[pos] = arr[i];
			pos++;
		}
		
		for (int i = 0; i < position; i++) {
			temp[pos] = arr[i];
			pos++;
		}

		delete[] arr;
		arr = temp;
	
	}
}

//////////////////////
// helper functions //
//////////////////////

// helper method for deep copy
template <typename T>
void ArrayClass<T>::copyArray(const ArrayClass& ac)
{	
	_size = ac.size();
	_capacity = ac.capacity();

	T* temp = new T[_capacity];
	for (int i = 0; i < _size; i++) {
		temp[i] = ac.arr[i];
	}

	delete[] arr;
	arr = temp;
	
}

// helper method for expanding array
template <typename T>
void ArrayClass<T>::expandArray()
{	
	_capacity = _capacity * EXPANSIONFACTOR;	

	T* temp = new T[_capacity];
	
	for (int i = 0; i < _size; i++) {
		temp[i] = arr[i];
	}

	delete[] arr;
	arr = temp;
}

#endif
