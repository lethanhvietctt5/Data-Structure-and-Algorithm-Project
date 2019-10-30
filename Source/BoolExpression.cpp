#include "BoolExpression.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int countDashes(string c)
{
	//TODO: đếm số dấu '-' trong biểu thức nhị phân

	int count = 0;
	for (int index = 0; index < c.length(); index++)
	{
		if (c[index] == '-')
			count++;
	}

	return count;
}


string maxCell(string in)
{
	//TODO: tìm tế bào dài nhất
	string max = "";

	for (int index = 0; index < in.length(); index++)
	{
		// loại bỏ những phép toán và dấu ' '
		if (in[index] != '\'' && in[index] != '+' && in[index] != ' ')
		{
			// kiểm tra biến đã tồn tại trong maxCell hay chưa ?
			if (max.find(in[index]) > max.length())
				max.append(1, in[index]);
		}
	}

	return max;
}


bool checkCell(Cell a,vector<Cell> r)
{
	//TODO: kiểm tra xem a có tồn tại trong r hay không

	vector<Cell>::iterator index;
	const char* t1 = a.data.c_str();
	for (index = r.begin(); index < r.end(); index++)
	{
		const char* t2 = (*index).data.c_str();
		if (strcmp(t1, t2) == 0)
			return false;
	}
	return true;
}

BoolExpression::BoolExpression()
{
}


BoolExpression::~BoolExpression()
{
}

bool BoolExpression::Column::ableToCombine(int i, int a, int b)
{
	int diff = 0;
	for (int m = 0; m < col[0].Exp[0].data.size(); m++)
	{
		if (col[i].Exp[a].data[m] != col[i + 1].Exp[b].data[m]) diff++;
	}
	if (diff == 1) return true;
	return false;
}

Cell BoolExpression::Column::Combine(int i, int a, int b)
{
	Cell result;
	for (int m = 0; m < col[i].Exp[a].data.size(); m++)
	{
		if (col[i].Exp[a].data[m] != col[i + 1].Exp[b].data[m]) 
			result.data += '-';
		else result.data += col[i].Exp[a].data[m];
	}
	for (int m = 0; m < col[i].Exp[a].data.size(); m++)
	{
		if  (result.data[i] == 1) result.type++;
	}
	return result;
}

BoolExpression::Column BoolExpression::creatColumn()
{	//TODO: tạo cột gồm các nhóm biểu thức có cùng số lượng số 1 trong biểu diễn
	Column result;
	//cấp phát bộ nhớ cho biến result
	result.col.resize(Exp[0].data.size() + 1);
	for (int i = 0; i < Exp[0].data.size()+1; i++)
	{
		result.col[i].Exp.clear();
	}
	for (int i = 0; i < Exp.size(); i++)
	{
		for (int k = 0; k < Exp[i].data.size(); k++)
		{	//vòng lặp này dùng để phân loại các biểu thức và ghi vào biến type
			if (Exp[i].data[k] == '1') Exp[i].type++;
		}
	}
	for (int i = 0; i < Exp.size(); i++)
	{	//đưa các biểu thức vào nhóm thích hợp
		result.col[Exp[i].type].Exp.push_back(this->Exp[i]);
	}
	for (int i = 0; i < result.col.size(); i++)
	{
		if (result.col[i].Exp.size() == 0)
		{	// xóa các nhóm bị trống
			result.col.erase(result.col.begin() + i);
			i--;
		}
	}
	return result;
}

vector<BoolExpression::Column> BoolExpression::creatTable()
{	
	//TODO: Tạo bảng gồm các cột (cột sau là kết quả nhân tổ hợp của cột trước nó)
	vector<Column> result;
	Column checking;
	checking = this->creatColumn();
	do
	{
		Column temp;
		for (int i = 0; i < checking.col.size() - 1; i++)
		{
			BoolExpression Combined;
			for (int a = 0; a < checking.col[i].Exp.size(); a++)
			{
				for (int b = 0; b < checking.col[i + 1].Exp.size(); b++)
				{
					if (checking.ableToCombine(i, a, b) == 1)
					{
						Cell newCell = checking.Combine(i, a, b);
						bool isDuplicated = false;
						for (int k = 0; k < Combined.Exp.size(); k++)
						{	// kiểm tra xem trong Combined đã có kết quả này hay chưa
							if (strcmp(newCell.data.c_str(), Combined.Exp[k].data.c_str()) == 0)
							{	isDuplicated = true;	}
						}	// nếu có thì thêm vào vector Combined
						if (isDuplicated == false)
							Combined.Exp.push_back(checking.Combine(i, a, b));
						checking.col[i].Exp[a].isCombined = true;
						checking.col[i + 1].Exp[b].isCombined = true;
					}
				}
			}
			if (Combined.Exp.size() != 0)
				temp.col.push_back(Combined);
		}
		result.push_back(checking);
		if (!checking.continueCombine())
		{	// điều kiện dừng vòng lặp
			break;
		}
		checking = temp;
	} while (true);
	return result;
}


string BoolExpression::inputBoolExpression()
{
	//TODO: Nhập vào biểu thức bool 
	string result;

	cout << "Enter Your Bool Expression:" << endl;
	cin.ignore();
	getline(cin, result);
	return result;
}


void BoolExpression::creatCell()
{
	//TODO: tạo các tế bào con và biến đổi nhị phân

	vector<Cell> result;

	// Tách chuỗi
	string in = inputBoolExpression();
	int len = in.length();
	int index = 0;
	while (index < len && in.find('+', index) < len)
	{
		// vòng lặp tách chuỗi input thành những biểu thức con
		size_t index_find = in.find('+', index);
		while (in[index_find - 1] == ' ') index_find--;
		string temp = in.substr(index, index_find - index);
		Cell tmp;
		tmp.cell = temp;
		result.push_back(tmp);
		while (in[index_find + 1] == '+' || in[index_find + 1] == ' ') index_find++;
		index = index_find + 1;
		temp = "";
	}

	// Thêm biểu thức con sau dấu '+' cuối cùng vào chuỗi các biểu thức
	string temp = in.substr(index);
	Cell tmp;
	tmp.cell = temp;
	result.push_back(tmp);

	// Phân tích biểu thức theo thứ tự các biến truyền vào
	vector<Cell>::iterator i;
	Cell L ;
	L.cell = maxCell(in);
	MaxCell = maxCell(in);

	for (i = result.begin(); i < result.end(); i++)
	{
		string t = "";

		for (int j = 0; j < L.cell.length(); j++)
		{
			bool check = false;
			for (int k = 0; k < (*i).cell.length(); k++)
			{
				if ((*i).cell[k] == L.cell[j])
				{
					t.append(1, (*i).cell[k]);
					if ((k < (*i).cell.length() - 1) && ((*i).cell[k + 1] == '\''))
						t.append(1, (*i).cell[k + 1]);
					check = true;
					break;
				}
			}

			if (check == false)
				t.append(" ");
		}

		(*i).cell = t;
	}

	// đổi sang nhị phân
	for (i = result.begin(); i < result.end(); i++)
	{
		for (int k = 0; k < (*i).cell.length(); k++)
		{
			if ((*i).cell[k] == '\'')
				(*i).data.replace((*i).data.length() - 1, 1, "0");

			else if ((*i).cell[k] == ' ')
				(*i).data.append("-");
			
			else
				(*i).data.append("1");
			
		}
	}

	// Những biểu thức sau khi đổi sang dạng nhị phân có chứa '-' sẽ cho ra nhiều biểu thức nhị phân khác
	vector<Cell> r;
	vector<Cell> r1;
	for (i = result.begin(); i < result.end(); i++)
	{
		// đếm số dấu '-' trong biểu thức con
		int dashes = countDashes((*i).data);

		if (dashes == 0)
			r1.push_back((*i));

		else if (dashes > 0)
		{
			int j = (*i).data.find('-');

			(*i).data[j] = '0';
			Cell t;
			t.data = (*i).data;
			r.push_back(t);

			(*i).data[j] = '1';
			t.data = (*i).data;
			r.push_back(t);

			vector<Cell>::iterator k;
			for (int index = 0; index < dashes - 1; index++)
			{
				vector<Cell> r2;
				for (k = r.begin(); k < r.end(); k++)
				{
					int i_find = (*k).data.find('-');
					(*k).data[i_find] = '0';
					Cell t2;
					t2.data = (*k).data;
					r2.push_back(t2);

					(*k).data[i_find] = '1';
					t2.data = (*k).data;
					r2.push_back(t2);
				}

				r = r2;
				r2.clear();
			}
		}

		// Thêm những biểu thức con sau khi đã biến đổi và chưa tồn tại trong Exp vào Exp 
		vector<Cell>::iterator k;

		for (k = r1.begin(); k < r1.end(); k++)
		{
			if (checkCell((*k), Exp) == true)
				Exp.push_back((*k));
		}

		for (k = r.begin(); k < r.end(); k++)
		{
			if (checkCell((*k), Exp) == true)
				Exp.push_back((*k));
		}

		r.clear();
		r1.clear();
	}
}


bool BoolExpression::compare(int i, Cell a)
{
	//TODO: so sánh để kiểm tra a có tồn tại trong Exp[i] hay không ?
	for (int index = 0; index < a.data.length(); index++)
	{
		if (a.data[index] != '-' && a.data[index] != Exp[i].data[index])
			return false;
	}
	return true;
}


BoolExpression BoolExpression::compactExpression()
{	//TODO: trả về biểu thức rút gọn của input
	BoolExpression result;
	vector<Column> table = this->creatTable();
	for (int i = 0; i < table.size(); i++)
	{
		for (int j = 0; j < table[i].col.size(); j++)
		{
			for (int k = 0; k < table[i].col[j].Exp.size(); k++)
			{
				if (table[i].col[j].Exp[k].isCombined == false)
					result.Exp.push_back(table[i].col[j].Exp[k]);
			}
		}
	}
	return result;
}

bool BoolExpression::Column::continueCombine()
{	//TODO: Kiểm tra có tiếp tục nhân các biểu thức với nhau không
	for (int i = 0; i < col.size(); i++)
	{
		for (int j = 0; j < col[i].Exp.size(); j++)
		{
			if (col[i].Exp[j].isCombined)
				return true;
		}
	}
	return false;
}

int checkColumn(vector<vector<int>> table, int col)
{
	//TODO: kiểm tra cột có tồn tại nguyên nhân nguyên tố cốt yếu không? (Nếu không có trả về -1, có trả về vị trí của nguyên tố đó)
	int count = 0, index;
	for (int i = 0; i < table.size(); i++)
	{
		if (table[i][col] == 1){
			count++; index = i;
		}
	}
	if (count == 1) return index;
	return -1;
}

void getAllPossibleCombine(vector<set<int>> &pat_Exp, int count, set<int> temp, set< set<int> > &posComb)
{
	 //TODO: hàm đệ quy điền vào biến posComb tất cả các kết quả của phép nhân các biểu thức logic có trong pat_Exp

	if (count == pat_Exp.size())
	{	//đến biểu thức cuối thì dừng và đưa kết quả phép nhân vào posComb
		set<int> a = temp;
		posComb.insert(temp);
		return;
	}
	else{
		for (set<int > ::iterator itr = pat_Exp[count].begin(); itr != pat_Exp[count].end(); ++itr)
		{
			//TODO: vòng lặp chạy tất cả các biến trong pat_Exp và nhân lần lượt với nhau
			int x = *itr;
			bool inserted = temp.insert(x).second;	//dùng .second để kiểm tra có insert thành công hay không
			getAllPossibleCombine(pat_Exp, count + 1, temp, posComb);
			if (inserted)
			{	//nếu đã insert thành công và gán vào posComb (trong hàm đệ quy) thì xóa temp đi
				temp.erase(x);
			}
		}
	}
}

vector<set<int>> patricksMethod(vector<vector<int>> table)
{	
	//TODO: hàm trả về 1 vector các kết hợp tối thiểu bằng phương pháp Petrick.

	vector<set<int>> result;	//Biến để lưu các biểu có số biến nhỏ nhất (đơn giản nhất) trong posComb
	vector<set<int>> pat_Exp;

	for(int col = 0; col < table[0].size(); col++)
	{ //Kiểm tra từng cột và điền vào pat_Exp các biểu thức logic P(1, 2, ...)
		set<int> x;
		for (int row = 0; row < table.size(); row++)
		{
			if (table[row][col] == 1)
			{
				x.insert(row);
			}
		}
		pat_Exp.push_back(x);
	}

	set< set<int> > posComb;	//posComb để lưu tất cả các kết quả của phép nhân các biểu thức Logic
	set<int> temp;	//temp sử dụng để truyền vào hàm đệ quy getAllPossibleCombine
	getAllPossibleCombine(pat_Exp, 0, temp, posComb);
	int min = INT_MAX;	//biến min để lưu số biến của biểu thức đơn giản nhất trong posComb 

	for (set<set<int>> ::iterator a = posComb.begin(); a != posComb.end(); ++a)
	{	//lặp qua các phần tử của posComb
		set<int> comb = *a;
		min = (comb.size() < min) ? comb.size() : min; //nếu số biển của biểu thức này nhỏ hơn min thì gán min bằng nó
	}
	
	for (set<set<int>> ::iterator a = posComb.begin(); a != posComb.end(); ++a)
	{	//lặp qua các phần tử của posComb
		set<int> comb = *a;
		if (comb.size() == min)
		{	//đưa vào result các tổ hợp có độ phức tạp bé nhất
			result.push_back(comb);
		}
	}

	return result;
}

int countElements(Cell a)
{
	int count = 0;
	for (int i = 0; i < a.data.size(); i++)
	{
		if (a.data[i] != '-') count++;
	}
	return count;
}

void BoolExpression::simplifyExpression()
{
	//TODO: tìm và in ra các biểu thức tối thiểu của hàm bool, sử dụng phương pháp Quine - Mccluskey.
	vector<BoolExpression> result;
	BoolExpression essential, input = *this	// biến essential để lưu các biểu thức logic bắt buộc phải chọn 
		, compactExp = compactExpression();	// biến compactExp chứa các biểu thức logic sau khi rút gọn hàm bool
	vector<vector<int>> table;
	essential.MaxCell = this->MaxCell;
	// cấp phát bộ nhớ cho vector table
	table.resize(compactExp.Exp.size());
	for (int i = 0; i < compactExp.Exp.size(); i++)
	{
		table[i].resize(input.Exp.size());
		for (int j = 0; j < this->Exp.size(); j++)
		{
			table[i][j] = (this->compare(j, compactExp.Exp[i])) ? 1 : 0;
		}
	}

	for (int i = 0; i < table[0].size(); i++)
	{
		int row = checkColumn(table, i);
		if (row != -1)
		{	//nếu là nguyên nhân nguyên tố cốt yếu thì chọn phần tử đó và xóa hết những cột được phủ bởi nó.
			essential.Exp.push_back(compactExp.Exp[row]);
			for (int k = 0; k < table[0].size(); k++)
			{	//kiểm tra trên dòng row có tồn tại số 1 nào không, nếu có thì xóa cột đó
				if (table[row][k] == 1)
				{
					input.Exp.erase(input.Exp.begin() + k);
					for (int m = 0; m < table.size(); m++)
					{//xóa cột thứ k
						table[m].erase(table[m].begin() + k);
					}
					k--;
				}
			}
			i--; //trừ biến i với số cột bị xóa để không bị sai vị trí
		}
	}
	for (int i = 0; i < table.size(); i++)
	{ //xóa những hàng chỉ toàn số 0 còn lại
		int check = 0;
		for (int j = 0; j < table[i].size(); j++)
		{
			if (table[i][j] == 1)
			{
				check = 1; break;
			}
		}
		if (check == 0)
		{	// Nếu dòng i toàn kí tự 0 thì xóa đi 
			compactExp.Exp.erase(compactExp.Exp.begin() + i);
			table.erase(table.begin() + i);
			i--;
		}
	}
	if (table.size() == 0)
	{	// Nếu không cần chọn biểu thức nào nữa thì gắn result = essential
		result.push_back(essential);
	}
	else
	{
		vector<set<int>> temp = patricksMethod(table);	// tìm các tổ hợp có số biểu thức nhỏ nhất phù hợp.
		int min_elements = INT_MAX;	// biến lưu số biến nhỏ nhất trong 1 tổ hợp biểu thức
		vector<int> n_elements;	// vector lưu số biển trong các tổ hợp biểu thức của temp trả về
		n_elements.resize(temp.size());	// chuỗi chứa số biến có trong 1 tổ hợp các biểu thức
		for (int i = 0; i < temp.size(); i++)
		{
			for (set<int> ::iterator itr = temp[i].begin(); itr != temp[i].end(); ++itr)
				{	//duyệt qua các phần tử của temp
				int x = *itr;
				n_elements[i] += countElements(compactExp.Exp[x]);	
				// cộng vào biến đếm số biến của biểu thức compactExp.Exp[i]
				}	
			min_elements = (n_elements[i] < min_elements) ? n_elements[i] : min_elements;
		}

		for (int i = 0; i < temp.size(); i++)
		{
			if (n_elements[i] == min_elements)
			{
				BoolExpression res_temp = essential;
				for (set<int > ::iterator itr = temp[i].begin(); itr != temp[i].end(); ++itr)
				{	//duyệt qua các phần tử của temp
					int x = *itr;
					res_temp.Exp.push_back(compactExp.Exp[x]);
					//gán vào res_temp các tổ hợp biểu thức logic tối thiểu được chọn
				}
				result.push_back(res_temp);
			}
		}
	}
	cout << endl << "====All expression(s) after simplify====" << endl;
	for (int i = 0; i < result.size(); i++)
	{	//in ra kết quả
		result[i].printExpression();
		cout << endl;
	}
}

void BoolExpression::printExpression()
{
	//TODO: In ra biểu thức
	string exp = "";
	string exp_t;
	vector<Cell>::iterator index;

	for (index = Exp.begin(); index < Exp.end(); index++)
	{
		for (int i = 0; i < (*index).data.length(); i++)
		{
			if ((*index).data[i] == '1')
				exp.append(1, MaxCell[i]);
			else if ((*index).data[i] == '0')
			{
				exp.append(1, MaxCell[i]);
				exp.append(1, '\'');
			}
		}
		exp.append(1, ' ');
		exp.append(1, '+');
		exp.append(1, ' ');
	}

	exp.pop_back();
	exp.pop_back();
	exp.pop_back();

	if (exp.length()==0)
		cout << "Always true";
	else
		cout << exp;
}