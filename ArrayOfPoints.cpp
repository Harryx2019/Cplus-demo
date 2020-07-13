#include <iostream>
#include <cassert>
#include "Point.h"
#include "ArryayOfPoints.h"
using namespace std;

ArrayOfPoints::ArrayOfPoints(int size): size(size) {
	points = new Point[size];
}

ArrayOfPoints::~ArrayOfPoints() {
	cout << "Deleting..." << endl;
	delete[] points;
}

Point& ArrayOfPoints::element(int index) {
	assert(index >= 0 && index < size);
	return points[index];
}

void CreateArrayOfPoints() {
	int count;
	cout << "Please enter the count of points:";
	cin >> count;
	ArrayOfPoints points(count);
	points.element(0).move(5, 0);
	points.element(1).move(15, 20);
}