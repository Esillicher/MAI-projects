#include "libs.h"

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



double polinom1(vector<double> x, vector<double> y, double sum_x, double sum_x2, double sum_y, double sum_yx, int n, int k)
{
	vector <vector <double>> A, L, U;
	vector <double> b, a , f;

	A.resize(k);
	L.resize(k);
	U.resize(k);
	b.resize(k,0);
	a.resize(k,0);
	f.resize(n, 0);
	for (int i = 0; i < k; ++i)
	{
		A[i].resize(k, 0);
		L[i].resize(k, 0);
		U[i].resize(k, 0);
	}
	
	A[0][0] = (n);
	A[1][0] = sum_x;
	A[0][1] = sum_x;
	A[1][1] = sum_x2;
	b[0] = sum_y;
	b[1] = sum_yx;

	cout << "Полином 1-й степени" << endl;

	LU(A, L, U, k);
	a = SLAU(A, L, U, b, k);
	for (int i = 0; i < k; ++i)
		cout << "a[" << i + 1 << "] = " << a[i] << endl;

	for (int i = 0; i < n; ++i)
		f[i] = a[0] + a[1] * x[i];
	cout << setw(8) << "i" << setw(8) << "0" << setw(8) << "1" << setw(8) << "2" << setw(8) << "3" << setw(8) << "4" << setw(8) << "5" << endl;
	cout << setw(8) << "x_i" << setw(8) << x[0] << setw(8) << x[1] << setw(8) << x[2] << setw(8) << x[3] << setw(8) << x[4] << setw(8) << x[5] << endl;
	cout << setw(8) << "F1(xi)" << setw(8) << f[0] << setw(8) << f[1] << setw(8) << f[2] << setw(8) << f[3] << setw(8) << f[4] << setw(8) << f[5] << endl;

	double F = 0;
	for (int i = 0; i < n; ++i)
		F += pow(f[i] - y[i], 2);

	cout << "Cумма квадратов ошибок Ф = " << F << endl;
	return F;

}

double polinom2(vector<double> x, vector<double> y, double sum_x, double sum_x2, double sum_x3, double sum_x4, double sum_y, double sum_yx, double sum_yx2, int n, int k)
{
	vector <vector <double>> A, L, U;
	vector <double> b, a, f;

	A.resize(k+1);
	L.resize(k+1);
	U.resize(k+1);
	b.resize(k + 1, 0);
	a.resize(k + 1, 0);
	f.resize(n, 0);
	for (int i = 0; i < k + 1; ++i)
	{
		A[i].resize(k + 1, 0);
		L[i].resize(k + 1, 0);
		U[i].resize(k + 1, 0);
	}

	A[0][0] = (n);
	A[1][0] = sum_x;
	A[2][0] = sum_x2;
	A[0][1] = sum_x;
	A[1][1] = sum_x2;
	A[2][1] = sum_x3;
	A[0][2] = sum_x2;
	A[1][2] = sum_x3;
	A[2][2] = sum_x4;
	b[0] = sum_y;
	b[1] = sum_yx;
	b[2] = sum_yx2;

	cout << "Полином 2-й степени" << endl;

	LU(A, L, U, k+1);
	a = SLAU(A, L, U, b, k+1);
	for (int i = 0; i < k+1; ++i)
		cout << "a[" << i + 1 << "] = " << a[i] << endl;
	cout << endl;

	for (int i = 0; i < n; ++i)
		f[i] = a[0] + a[1] * x[i]+a[2]*pow(x[i],2);
	cout << setw(8) << "i" << "|" << setw(8) << "0" << "|" << setw(8) << "1" << "|" << setw(8) << "2" << "|" << setw(8) << "3" << "|" << setw(8) << "4" << "|" << setw(8) << "5" << endl;
	cout << setw(8) << "x_i" << "|" << setw(8) << x[0] << "|" << setw(8) << x[1] << "|" << setw(8) << x[2] << "|" << setw(8) << x[3] << "|" << setw(8) << x[4] << "|" << setw(8) << x[5] << endl;
	cout << setw(8) << "F2(xi)" << "|" << setw(8) << f[0] << "|" << setw(8) << f[1] << "|" << setw(8) << f[2] << "|" << setw(8) << f[3] << "|" << setw(8) << f[4] << "|" << setw(8) << f[5] << endl;
	cout << endl;

	double F = 0;
	for (int i = 0; i < n; ++i)
		F += pow(f[i] - y[i], 2);

	cout << "Cумма квадратов ошибок Ф = " << F << endl;
	return F;

}

void MNK_main()
{
	 
	int n;
	int k=2;
	double sum_x = 0;
	double sum_y = 0;
	double sum_yx = 0;
	double sum_yx2 = 0;
	double sum_x2 = 0;
	double sum_x3 = 0;
	double sum_x4 = 0;
	ifstream test("test3-MNK.txt");
	test >> n;
	
	vector <double> x, y;

	x.resize(n);
	y.resize(n);
	for (int i = 0; i < n; ++i)
	{
		test >> x[i];
		test >> y[i];
	}

	for (int i = 0; i < n; ++i)
	{
		sum_x += x[i];
		sum_y += y[i];
		sum_yx += y[i]*x[i];
		sum_yx2 += y[i]*pow(x[i],2);
		sum_x2 += pow(x[i], 2);
		sum_x3 += pow(x[i], 3);
		sum_x4 += pow(x[i], 4);
	}

	polinom1(x,y,sum_x, sum_x2, sum_y, sum_yx, n, k);
	cout << endl;
	polinom2(x, y, sum_x, sum_x2, sum_x3, sum_x4, sum_y, sum_yx, sum_yx2, n, k);
}