#include "libs.h"

void show(vector <vector <double>> A, int n)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cout << setw(9) << fixed << setprecision(5) << A[i][j] << "   ";
		}
		cout << endl;
	}
	cout << endl;
}

void show(vector <double> x, int n)
{
	for (int i = 0; i < n; ++i)
		cout << setw(9) << fixed << setprecision(5) << x[i] << "   " << endl;

	cout << endl;
}

double det(vector <vector <double>> U, int n)
{
	double det = 1;
	for (int i = 0; i < n; ++i)
		det *= U[i][i];
	return det;
}

vector<vector<double>> transpose(vector <vector<double>> M, int n)
{
	for (int i = 0; i < n; ++i)
		for (int j = i; j < n; ++j)
			swap(M[i][j], M[j][i]);

	return M;
}

vector<vector<double>> proisv(vector <vector <double>> A, vector <vector <double>> B, int n)
{
	vector<vector<double>> R;
	R.resize(n);

	for (int i = 0; i < n; ++i)
	{
		R[i].resize(n, 0);
		for (int j = 0; j < n; ++j)
			for (int k = 0; k < n; ++k)
				R[i][j] += A[i][k] * B[k][j];
	}
	return R;
}

void LU(vector <vector <double>> A, vector <vector <double>> &L,
	vector <vector <double>> &U, int n)
{
	for (int j = 0; j < n; ++j)
		U[0][j] = A[0][j];

	for (int i = 0; i < n; ++i)
		L[i][0] = A[i][0] / U[0][0];

	for (int i = 1; i < n; ++i)
	{
		for (int j = i; j < n; ++j)
		{
			double sum = 0;
			for (int k = 0; k < i; ++k)
				sum += L[i][k] * U[k][j];
			U[i][j] = A[i][j] - sum;

			sum = 0;
			for (int k = 0; k < i; ++k)
				sum += L[j][k] * U[k][i];
			L[j][i] = (A[j][i] - sum) / U[i][i];
		}
	}
}

vector<double> SLAU(vector <vector <double>> A, vector <vector <double>> L,
	vector <vector <double>> U, vector <double> b, int n)
{
	vector <double> x, z;
	x.resize(n, 0);
	z.resize(n, 0);

	z[0] = b[0];

	for (int i = 1; i < n; ++i)
	{
		double sum = 0;
		for (int j = 0; j < i; ++j)
			sum += L[i][j] * z[j];
		z[i] = b[i] - sum;
	}

	x[n - 1] = z[n - 1] / U[n - 1][n - 1];

	for (int i = n - 2; i >= 0; --i)
	{
		double sum = 0;
		for (int j = i + 1; j < n; ++j)
			sum += U[i][j] * x[j];
		x[i] = (z[i] - sum) / U[i][i];
	}
	return x;
}

vector <vector <double>> InverseMatrix(vector <vector <double>> A, vector <vector <double>> L, vector <vector <double>> U, int n)
{
	vector <vector<double>> e, x, y;
	vector <vector <vector <double>>> newL, newU;
	e.resize(n);
	x.resize(n);
	y.resize(n);
	newL.resize(2 * n);
	newU.resize(2 * n);

	for (int i = 0; i < n; ++i)
	{
		e[i].resize(n, 0);
		x[i].resize(n, 0);
		y[i].resize(n, 0);
		e[i][i] = 1;
	}

	for (int i = 0; i < 2 * n; ++i)
	{
		newL[i].resize(n);
		newU[i].resize(n);
		for (int j = 0; j < n; ++j)
		{
			newL[i][j].resize(n, 0);
			newU[i][j].resize(n, 0);
		}
	}

	for (int i = 0; i < n; ++i)
	{
		LU(L, newL[i], newU[i], n);
		LU(U, newL[i + n], newU[i + n], n);
		x[i] = SLAU(U, newL[i + n], newU[i + n], SLAU(L, newL[i], newU[i], e[i], n), n);
	}
	return transpose(x, n);
}

void LU_main()
{
	int n;
	ifstream test ("test1-LU.txt");
	test >> n;

	vector <vector <double>> A, L, U;
	vector <double> b;

	A.resize(n);
	L.resize(n);
	U.resize(n);
	b.resize(n);
	for (int i = 0; i < n; ++i)
	{
		A[i].resize(n, 0);
		L[i].resize(n, 0);
		U[i].resize(n, 0);
		for (int j = 0; j < n; ++j)
		{
			test >> A[i][j];
		}
		test >> b[i];
	}

	LU(A, L, U, n);
	cout << "Исходная матрица коэффициентов:" << endl;
	show(A, n);
	cout << "Матрица U:" << endl;
	show(U, n);
	cout << "Матрица L:" << endl;
	show(L, n);
	cout << "Произведение L*U:" << endl;
	show(proisv(L, U, n), n);
	cout << "det A = " << det(U, n) << endl << endl;
	cout << "Решение СЛАУ: " << endl;
	show(SLAU(A, L, U, b, n), n);
	cout << "Обратная матрица A^-1:" << endl;
	show(InverseMatrix(A, L, U, n), n);

	cout << endl << endl;
	test.close();
}