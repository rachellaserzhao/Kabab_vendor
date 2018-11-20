#include "stack.h"
#include "arrayclass.h"
#include <iostream>
#include <cmath>


#ifdef _STACK_H_

template <typename T>
Stack<T>::Stack(){

}

template <typename T>
Stack<T>::Stack(const Stack& st){
	ac=st.ac;
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& st){
	for (unsigned int i = 0; i < ac.size(); i++){
		pop();
	}
	ac=st.ac;
	return *this;
}
template <typename T>
bool Stack<T>::isEmpty() const{
	return ac.empty();
}

template <typename T>
unsigned int Stack<T>::size() const{
	return ac.size();
}

template <typename T>
T& Stack<T>::peek() {
	return ac.back();
}

template <typename T>
void Stack<T>::push(const T item){
	ac.pushBack(item);
}

template <typename T>
T Stack<T>::pop(){
	
	T temp = ac.back();
	ac.popBack();
	return temp;
}

#endif