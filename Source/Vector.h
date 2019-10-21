#pragma once
#include <iostream>
class Vector
{
	int n;
	double* data;
public:
	void inputVector();
	void showVector();
	Vector(const Vector &a);
	Vector();
	Vector& operator = (const Vector &a);
	~Vector();
	Vector operator +(const Vector &a);
	Vector operator *(double x);
	bool isEmpty();
};

