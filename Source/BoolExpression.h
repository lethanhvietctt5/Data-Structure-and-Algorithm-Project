#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <set>

using namespace std;

struct Cell{
	string data = "";	// biểu thức dưới dạng nhị phân (0,1)
	string cell = "";	// biểu thức dưới dạng biến (x,y,z,...)
	bool isCombined = false;
	int type = 0;
	//phân loại theo số lượng số 1 trong tế bào.
};

class BoolExpression
{
private:
	vector<Cell> Exp;	// tập hợp các biểu thức 
	string MaxCell;		// chuỗi chưa tất cả các biến
	class Column
	{
	public:
		vector<BoolExpression> col;
		bool ableToCombine(int i, int a, int b);
		Cell Combine(int i, int a, int b);
		bool continueCombine();
	};

public:
	Column creatColumn();
	vector<Column> creatTable();	// Tạo bảng lưu thông tin cho hàm simplifyExpression
	BoolExpression compactExpression();	// Tìm và trả về biểu thức rút gọn của hàm bool
	void simplifyExpression();	// Tìm và xuất ra các biểu thức tối giản của hàm bool
	string inputBoolExpression();		// Nhập biểu thức bool
	void creatCell();		// khởi tạo tế bào từ biểu thức input
	bool compare(int i, Cell a);	// so sánh để kiểm tra a có tồn tại trong Exp không
	void printExpression();		// In biểu thức
	BoolExpression();
	~BoolExpression();
};