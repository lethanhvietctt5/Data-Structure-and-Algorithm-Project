#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "BoolExpression.h"
#include "Matrix.h"

using namespace std;

void Bool()
{
	/*while (_kbhit()) _getch();*/
	system("cls");
	cout << "           ==========================================" << endl;
	cout << "                    SIMPLIFY BOOL EXPRESSION         " << endl;
	cout << "           ==========================================" << endl;
	cout << endl << endl;
	BoolExpression b;

	cout << "			RULES :" << endl;
	cout << "				not A   -> A'" << endl;
	cout << "				A and B -> AB" << endl;
	cout << "				A or B  -> A+B" << endl;

	cout << endl << endl;
	b.creatCell();
	cout << endl;
	cout << "=================RESULT=================" << endl;
	b.simplifyExpression();
}

void matrix()
{
	system("cls");
	cout << "           ==========================================" << endl;
	cout << "                      OPERATIONS WITH MATRIX         " << endl;
	cout << "           ==========================================" << endl;
	cout << endl << endl;

	int choose;

	cout << "	1.Caculate Determination of Matrix." << endl;
	cout << "	2.Inverse Matrix." << endl;
	cout << "	3.Mutiply two Matrics." << endl;
	cout << "	4.Find Rank of Matrix." << endl;
	cout << "	5.Solve System of Linear Equation." << endl;
	cout << "=================================================================================" << endl;
	cout << "Your choose: "; cin >> choose;

	switch (choose)
	{
	case 1:
	{
		Matrix m;
		cout << "Enter matrix:" << endl;
		int det = m.determinantMatrix();
		if (det < 0)
			cout << "Matrix don't have determination." << endl;
		else
		{
			cout << "Determination of Matrix: " << det << endl;
		}
		break;
	}
	case 2:
		break;
	case 3:
	{
		Matrix m1, m2, m3;
		cout << "Enter the first matrix:" << endl;
		m1.inputMatrix();
		cout << "Enter the second matrix:" << endl;
		m2.inputMatrix();

		m3 = m1 * m2;

		if (m3.isEmpty())
			cout << "Number of columns of 1st matrix MUST BE EQUAL TO number of rows of 2nd matrix" << endl;
		else
		{
			cout << "Matrix result:" << endl;
			m3.showMatrix();
		}
		break;
	}
	case 4:
	{
		Matrix m;
		cout << "Enter Matrix:" << endl;
		m.inputMatrix();
		cout << "Rank of Matrix: " << m.rankMatrix();
		break;
	}
	case 5:
		break;
	default:
		break;
	}
}
int main()
{
	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		system("cls");
		cout << "                ============================================================" << endl;
		cout << "                            DATA STRUCTURE AND ALGORITHM PROJECT            " << endl;
		cout << "                ============================================================" << endl;
		cout << endl;
		cout << "                                1. Simplify Bool Expression." << endl;
		cout << "                                2. Operations with Vector." << endl;
		cout << "                                3. Operations with Matrix." << endl;
		cout <<endl << "        ===============================================================================" << endl;
		int choose;
		cout << "Your choose:"; cin >> choose;
		switch (choose)
		{
		case 1:
			Bool();
			break;
		case 2:
			break;
		case 3:
			matrix();
			break;
		default:
			break;
		}
		cout << endl << endl;
		cout << "Press any key to continue and Press ESC to exit." << endl;
		_getch();
	}
	return 0;
}