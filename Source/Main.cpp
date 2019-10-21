#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "BoolExpression.h"
#include "Matrix.h"
#include "Vector.h"

using namespace std;

void boolExpression()
{
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

void vectorOperations()
{
	system("cls");

	cout << "                ============================================================" << endl;
	cout << "                                     OPERATIONS WITH VECTOR            " << endl;
	cout << "                ============================================================" << endl;
	cout << endl;
	cout << "                                1.Addition 2 vector." << endl;
	cout << "                                2.Multiply a vector with alpha number."<< endl;
	cout << endl << "        ===============================================================================" << endl;
	int choose;
	cout << "Your choose: "; cin >> choose;
	switch (choose)
	{
	case 1:
	{
			  Vector v1, v2, v3;
			  cout << "Enter the first vector:" << endl;
			  v1.inputVector();
			  cout << "Enter the second vector:" << endl;
			  v2.inputVector();
			  
			  v3 = v1 + v2;
			  if (v3.isEmpty())
				  cout << "The length of two vectors must be equal.";
			  else
			  {
				  cout << endl << "Vector result:" << endl;
				  v3.showVector();
			  }

			  break;
	}
	case 2:
	{
			  Vector v, v2;
			  double alpha;
			  cout << "Enter vector:" << endl;
			  v.inputVector();
			  cout << "Enter alpha number:" << endl;
			  cin >> alpha;

			  v2 = v * alpha;
			  cout << endl << "Vector result:" << endl;
			  v2.showVector();
			  break;
	}
	default:
		break;
	}
}

void matrix()
{
	system("cls");

	cout << "                ============================================================" << endl;
	cout << "                                     OPERATIONS WITH MATRIX            " << endl;
	cout << "                ============================================================" << endl;
	cout << endl;
	cout << "                                1.Caculate Determination of Matrix." << endl;
	cout << "                                2.Inverse Matrix." << endl;
	cout << "                                3.Mutiply two Matrics." << endl;
	cout << "                                4.Find Rank of Matrix." << endl;
	cout << "                                5.Solve System of Linear Equation." << endl;
	cout << endl << "        ===============================================================================" << endl;
	int choose;
	cout << "Your choose: "; cin >> choose;
	switch (choose)
	{
	case 1:
	{
		Matrix m;
		cout <<"Enter matrix:" << endl;
		m.inputMatrix();
		int det = m.determinantMatrix();
		if (det == INT_MIN)
			cout << "Matrix don't have determination." << endl;
		else
		{
			cout << "Determination of Matrix: " << det << endl;
		}
		break;
	}
	case 2:
	{
		  Matrix m, m2;
		  cout << "Enter matrix:" << endl;
		  m.inputMatrix();
		  m2 = m.inverseMatrix();
		  if (m2.isEmpty())
			  cout << "Can't inverse this matrix.";
		  else
		  {
			  cout << "Inversed matrix:" << endl;
			  m2.showMatrix();
		  }
		  break;
	}
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
	{
		  int n_var, n_equation; // số biến và số phương trình
		  cout << "Enter number of variable(s):" << endl;
		  cin >> n_var;
		  cout << "Enter number of equation(s):" << endl;
		  cin >> n_equation;
		  Matrix m(n_equation, n_var + 1);
		  m.inputMatrix();
		  m.systemLinerEquation();
		  break;
	}
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
		cout << endl << "        ===============================================================================" << endl;
		int choose;
		cout << "Your choose:"; cin >> choose;
		switch (choose)
		{
		case 1:
			boolExpression();
			break;
		case 2:
			vectorOperations();
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