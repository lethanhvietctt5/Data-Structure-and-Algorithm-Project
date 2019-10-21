#include "Matrix.h"
#include <math.h>
#include <iostream>

using namespace std;

void swapRow(double** m, int row1, int row2, int col)
{
	// TODO: Hoán đổi dòng row1 với dòng row2 của ma trận m
	//Input: m là ma trận cần biến đổi, row1 và row2 là 2 dòng cần hoán đổi, col là số cột của ma trận

	for (int i = 0; i < col; i++)
	{
		double t = m[row1][i];
		m[row1][i] = m[row2][i];
		m[row2][i] = t;
	}
}

Matrix::Matrix()
{
	//TODO: Constructor mặc định

	_row = 0;
	_column = 0;
	_matrix = new double* [_row];
	
	for (int index = 0; index < _row; index++)
		_matrix[index] = new double[_column];
}


Matrix::Matrix(int r, int c)
{
	//TODO: Constructor tham số
	//Input: r là số dòng, c là số cột

	_row = r;
	_column = c;
	_matrix = new double* [_row];

	for (int index = 0; index < _row; index++)
		_matrix[index] = new double[_column];
}


Matrix::Matrix(int r, int c, double** m)
{
	//TODO: Constructor tham số
	//Input: r là số dòng, c là số cột, m là mảng chứa các phần tử của ma trận r*c

	_row = r;
	_column = c;
	_matrix = new double* [_row];

	// Cấp phát bộ nhớ
	for (int index = 0; index < _row; index++)
		_matrix[index] = new double[_column];

	// Sao chép từng phần tử vào ma trận
	for (int i_row = 0; i_row < _row; i_row++)
	{
		for (int i_col = 0; i_col < _column; i_col++)
		{
			_matrix[i_row][i_col] = m[i_row][i_col];
		}
	}
}


Matrix::Matrix(const Matrix& matrix)
{
	//TODO: Constructor copy
	//Input: ma trận cần copy

	_row = matrix._row;
	_column = matrix._column;
	_matrix = new double* [_row];

	// Cấp phát bộ nhớ
	for (int index = 0; index < _row; index++)
		_matrix[index] = new double[_column];


	// Sao chép từng phần tử vào ma trận
	for (int i_row = 0; i_row < _row; i_row++)
	{
		for (int i_col = 0; i_col < _column; i_col++)
		{
			_matrix[i_row][i_col] = matrix._matrix[i_row][i_col];
		}
	}
}

bool Matrix::isEmpty()
{
	if (_column == 0 || _row == 0)
		return true;
	return false;
}


double Matrix::determine(double** m,int n) // m là ma trận cần tính, n là kích cỡ của ma trận (nxn)
{
	//TODO: tính định thức của ma trận


	// Nếu ma trận 0 phần tử , return 0
	if (n < 0)
		return -1;

	// Nếu ma trận có 1 phần tử, return m[0][0]
	else if (n == 1)
		return m[0][0];

	// Nếu ma trận 2*2 có dạng A={{a,b},{c,d}} , return (a*d-b*c)
	else if (n == 2)
		return m[0][0] * m[1][1] - m[0][1] * m[1][0];
	

	
	double det = 0;		// giá trị ban đầu cho định thức

	for (int i = 0; i < n; i++)
	{
		// Cấp phát bộ nhớ cho ma trận _matrix(0,n), tức là ma trận con khi đã xóa dòng 0 và cột i 
		double** temp = new double* [n - 1];
		for (int index = 0; index < n - 1; index++)
		{
			temp[index] = new double[n - 1];
		}

		// xóa dòng 0 và cột i
		for (int row = 1; row < n; row++)
		{
			int r = row;
			int c = 0;
			for (int col = 0; col < n; col++)
			{
				if (col == i)
					continue;
				temp[r - 1][c++] = m[row][col];
			}
		}

		// đệ quy tính định thức 
		det += m[0][i] * pow(-1, 2 + i) * determine(temp, n - 1);
	}

	return det;
}


int Matrix::determinantMatrix()
{
	//TODO: trả về giá trị của định thức

	// Nhận input

	if (_row == 0 && _column == 0)
	{
		cout << "Enter number of rows = ";
		cin >> _row;
		cout << "Enter number of columns = ";
		cin >> _column;

		for (int index = 0; index < _row; index++)
			_matrix[index] = new double[_column];
	}

	if (_row != _column)

		return -1;


	// Nhập từng phần tử cho ma trận
	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _column; j++)
		{
			cout << "matrix[" << i << "]" << "[" << j << "]=";
			cin >> _matrix[i][j];
		}
	}

	return (int)determine(_matrix, _row);
}


Matrix Matrix::inverseMatrix()
{
	
	Matrix a;
	return a;
}


Matrix Matrix::operator *(const Matrix& m)	// m là ma trận được nhân với ma trận hiện tại
{
	//TODO: Nhân hai ma trận
	
	// Nếu không có dạng m*n nhân với n*p thì trả về ma trận rỗng
	Matrix tmp;
	if (_column != m._row)
		return tmp ;


	// cấp phát bộ nhớ cho mảng lưu giá trị của ma trận kết quả 
	double** result = new double* [_row];
	for (int index = 0; index < _row; index++)
		result[index] = new double[m._column];

	// Tính từng phần tử cho ma trận kết quả
	for (int i = 0; i < _row; i++)
	{
		int r = i;
		int c = 0;
		double sum = 0;

		for (int j = 0; j < m._column; j++)
		{
			sum = 0;

			for (int k = 0; k < _column; k++)
			{
				sum = sum + _matrix[i][k] * m._matrix[k][j];
			}

			result[r][c++] = sum;
		}
	}

	// Tạo ma trận kết quả và return
	Matrix a(_row, m._column, result);
	return a;
}


int Matrix::rankMatrix()
{
	//TODO: Tính hạng của ma trận
	// Thưc hiện theo phép biến đổi GAUSSIAN ELIMINATION

	//Sao chép ma trận lên một ma trận khác để biến đổi mà không ảnh hưởng đến ma trận gốc
	Matrix temp(_row,_column,_matrix);

	// Khởi tạo hạng ban đầu bằng số cột
	int rank = temp._column < temp._row ? temp._column : temp._row;

	for (int row = 0; row < rank; row++)
	{
		if (temp._matrix[row][row] != 0)
		{
			// Nếu phần tử tại [row][row] khác không thì lấy các phần tử của các dòng bên dưới TRỪ cho m lần dòng row
			for (int row1 = 0; row1 < temp._row; row1++)
			{
				if (row1 != row)
				{
					double m = temp._matrix[row1][row] / temp._matrix[row][row];
					for (int col = 0; col < rank; col++)
					{
						temp._matrix[row1][col] -= m * temp._matrix[row][col];
					}
				}
			}
		}

		else
		{
			// Nếu tại [row][row] bằng 0
			bool decrease = true;

			// Kiểm tra các phần tử cùng cột nếu có phần tử [row2][row] nào khác 0 thì đổi dòng row với dòng row2
			for (int row2 = row + 1; row2 < temp._row; row2++)
			{
				if (temp._matrix[row2][row] != 0)
				{
					swapRow(temp._matrix, row, row2, rank);
					decrease = false;
					break;
				}
			}

			// Nếu bước kiểm tra trên không tìm thấy phần tử a[row2][row] nào khác không thì hoán đổi cột row với cột rank
			if (decrease)
			{
				rank--;
				int c = row;
				for (int index = 0; index < temp._row; index++)
				{
					temp._matrix[index][c] = temp._matrix[index][rank];
				}
			}

			// giảm hàng đang xét để duyệt lại hàng vừa được hoán đổi
			row--;
		}
	}

	return rank;
}


void Matrix::systemLinerEquation()
{

}


void Matrix::inputMatrix()
{
	//TODO: Nhập số dòng, cột, và từng phần tử của ma trận

	// Kiểm tra nếu dòng và cột chưa có thì phải nhập
	if (_row == 0 && _column == 0)
	{
		cout << "Enter number of rows = ";
		cin >> _row;
		cout << "Enter number of columns = ";
		cin >> _column;

		for (int index = 0; index < _row; index++)
			_matrix[index] = new double[_column];
	}


	// Nhập từng phần tử cho ma trận
	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _column; j++)
		{
			cout << "matrix[" << i << "]" << "[" << j << "]=";
			cin >> _matrix[i][j];
		}
	}

	cout << endl << endl;
}


void Matrix::showMatrix()
{
	//TODO: In ra ma trận hiện tại

	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _column; j++)
		{
			cout << _matrix[i][j] << "  ";
		}
		cout << endl;
	}

	cout << endl;
}