#pragma once
#include "Point.h"
class ArrayOfPoints {
public:
	ArrayOfPoints(int size);
	~ArrayOfPoints();
	Point& element(int index);
private:
	Point* points;
	int size;
};

void CreateArrayOfPoints();