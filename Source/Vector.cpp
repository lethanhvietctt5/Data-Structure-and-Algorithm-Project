#include "Vector.h"


Vector::Vector()
{
	n = 0; data = NULL;
}

Vector::Vector(const Vector &a)
{
	n = a.n;
	data = new double[n];
	for (int i = 0; i < n; i++)
	{
		data[i] = a.data[i];
	}
}

Vector& Vector::operator = (const Vector &a)
{
	if (data != NULL)
	{
		delete[] data;
	}
	n = a.n;
	data = new double[n];
	for (int i = 0; i < n; i++)
	{
		data[i] = a.data[i];
	}
	return *this;
}

Vector::~Vector()
{
	delete[] data;
}

Vector Vector::operator +(const Vector &a)
{
	if (this->n != a.n) return Vector();	// nếu độ dài 2 vector không bằng nhau thì trả về mảng rỗng
	Vector result(*this);
	if (n == a.n)
	{
		for (int i = 0; i < n; i++)
		{
			result.data[i] = data[i] + a.data[i];	// cộng từng phần tử lại với nhau
		}
	}
	return result;
}

Vector Vector::operator *(double x)
{
	Vector result(*this);
	for (int i = 0; i < n; i++)
	{
		result.data[i] = data[i] * x;
	}
	return result;
}

void Vector::inputVector()
{
	std::cout << "Enter size of input vector: ";
	std::cin >> n;
	data = new double[n];
	for (int i = 0; i < n; i++)
	{
		std::cout << "vector[" << i + 1 << "]: ";
		std::cin >> data[i];
	}
}

void Vector::showVector()
{
	for  (int i = 0; i < n; i++)
	{
		std::cout << data[i] << " ";
	}std::cout << std::endl;
}

bool Vector::isEmpty()
{
	if (n == 0)
		return true;
	else return false;
}