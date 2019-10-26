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

	if (_row == 0 && _column == 0 || _row != _column)
		return INT_MIN;	// nếu không thể tìm định thức ma trận thì trả về INT_MIN
	return (int)determine(_matrix, _row);
}


Matrix Matrix::inverseMatrix()
{
	//tìm ma trận nghịch đảo bằng định lí Cramer
	int det = this->determinantMatrix();
	if (det == INT_MIN || det == 0) return Matrix();	//nếu ma trận không khả nghịch thì trả về ma trận rỗng 
	Matrix result(_row, _column), C(_row, _column);
	//result là ma trận ghi kết quả, C là ma trận phụ hợp của input
	// m là hệ số 1/|A|
	double m = 1.0 / det;
	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _column; j++)
		{	//temp là ma trận Xmn (ma trận input loại bỏ hàng m và cột n)
			Matrix temp(_row - 1, _column - 1);
			int i_temp = -1, j_temp = 0;
			for (int m = 0; m < _row; m++)
			{
				if (m != i)
				{
					j_temp = 0; i_temp++;
					for (int n = 0; n < _row; n++)
					{	//ghi kết quả vào ma trận Xmn
						if (n != j)	temp._matrix[i_temp][j_temp++] = _matrix[m][n];
					}
				}
			}
			C._matrix[i][j] = temp.determinantMatrix() * pow(-1.0, i + j);
		}
	}
	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _column; j++)
		{ //ma trận A^-1 = m * C(T)
			result._matrix[i][j] = m * C._matrix[j][i];
		}
	}
	return result;
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


Matrix Matrix::ChooseEquation(Matrix &x)
{ //TODO: chọn n phương trình cho hệ n ẩn (có nghiệm) để giải.
	//ma trận result sẽ có số dòng = số cột = số ẩn
	Matrix result(_column - 1, _column - 1);
	x._row = _column - 1;
	for (int i = _column - 1; i < x._row; i++)
	{
		delete[] x._matrix[i];
	}
	int i_result = 1, i_input = 1;
	result._matrix[0] = _matrix[0];
	x._matrix[0][0] = _matrix[0][_column - 1];
	for (int m = 0; m < _column - 1; m++)
		result._matrix[0][m] = _matrix[0][m];
	do
	{	//biến isDuplicated để kiểm tra phương trình _matrix[i_input] có tương đương với phương trình nào trong result không (1: có/ 0: không)
		int isDuplicated = 0;
		for (int i = 0; i < i_result; i++)
		{	//kiểm tra phương trình thứ i_input có trùng với phương trình nào trong result không
			double scale = result._matrix[i][0] / _matrix[i_input][0];
			int check = 1;
			for (int k = 1; k < _column; k++)
			{	//kiểm tra tỉ lệ của hệ số 2 phương trình có bằng với biến scale không, nếu có check = 0
				if (abs(result._matrix[i][k] / _matrix[i_input][k] - scale) > 0.0001)
				{
					check = 0; break;
				}
			}if (check == 1) isDuplicated = 1;
		}
		//nếu không trùng với phương trình nào thì thêm vào ma trận result
		if (isDuplicated == 0)
		{
			for (int m = 0; m < _column - 1; m++)
				result._matrix[i_result][m] = _matrix[i_input][m];
			x._matrix[i_result++][0] = _matrix[i_input][_column - 1];
		}
		i_input++;
	} while (i_result < _column - 1);
	return result;
}

void Matrix::systemLinerEquation()
{
	Matrix A(_row, _column - 1, _matrix);
	//A là ma trận hệ số của ma trận input.
	//Dùng hạng của ma trận để biện luận số nghiệm
	int this_R = this->rankMatrix(), A_R = A.rankMatrix();
	//phương trình vô nghiệm
	if (this_R == A_R + 1) std::cout << "The equation has no solution!!!" << std::endl;
	//phương trình có vô số nghiệm
	else if (this_R == A_R && this_R < _column - 1) std::cout << "The equation has countless solutions!!!" << std::endl;
	else if (this_R == A_R && this_R == _column - 1)
	{
		Matrix temp(_row, 1);
		if (_row > _column - 1)
		{ //trường hợp có nhiều phương trình hơn ẩn mà tồn tại nghiệm, chọn ra n phương trình không trùng nhau để giải
			A = this->ChooseEquation(temp);
		}
		else
		{
			for (int i = 0; i < _row; i++)
			{
				temp._matrix[i][0] = _matrix[i][_column - 1];
			}
		}
		A = A.inverseMatrix();
		temp = A * temp;
		std::cout << "The equation has only 1 solution: { ";
		for (int i = 0; i < _column - 1; i++)
		{
			std::cout << temp._matrix[i][0] << " ";
		}
		std::cout << "}" << std::endl;
	}
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