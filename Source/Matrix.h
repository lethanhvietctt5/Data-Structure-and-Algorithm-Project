#pragma once
class Matrix
{
	int _row;	// số hàng của ma trận	

	int _column;	// số cột của ma trận

	double** _matrix;	// mảng chứa các giá trị của ma trận
	
public:
	Matrix();	// Constructor mặc định

	Matrix(int r, int c);	// Constructor tham số

	Matrix(int r, int c,double** m);	// Constructor tham số

	Matrix(const Matrix& matrix);	// Constructor copy

	double determine(double** m,int n);		// hàm dùng để tính định thức của ma trận

	int determinantMatrix();	// Hàm trả về định thức của ma trận

	Matrix inverseMatrix();		// Hàm trả về ma trận nghịch đảo

	Matrix multiplyMatrix(const Matrix& m);		// Hàm nhân hai ma trận

	int rankMatrix();	// Hàm tính và trả về hạng của ma trận

	void systemLinerEquation();		// Hàm giải hệ phương trình tuyến tính

	void inputMatrix();			// Hàm nhập vào ma trận

	void showMatrix();		// Hàm in ra ma trận
};