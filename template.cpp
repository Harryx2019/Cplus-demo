#include <iostream>
#include <cstdlib>

#include "template.h"
using namespace std;

template<class T>
Store<T>::Store():haveValue(false){ }

template<class T>
T& Store<T>::getElem() {
	if (!haveValue) {
		cout << "No item present!" << endl;
		exit(1);
	}
	return item;
}

template<class T>
void Store<T>::putElem(const T& x) {
	haveValue = true;
	item = x;
}

void Template() {
	Store<int>s1, s2;
	s1.putElem(3);
	s2.putElem(-7);
	cout << s1.getElem() << " " << s2.getElem() << endl;

	Student g = { 1000,23 };
	Store<Student>s3;
	s3.putElem(g);
	cout << "The student id is " << s3.getElem().id << endl;

	Store<double>d;
	cout << "Retrieving object d..." << endl;
	cout << d.getElem() << endl;
}