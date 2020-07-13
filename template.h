#pragma once

struct Student
{
	int id;
	float gpa;
};

template<class T>
class Store {
private:
	T item;
	bool haveValue;
public:
	Store();
	T& getElem();
	void putElem(const T& x);
};

void Template();