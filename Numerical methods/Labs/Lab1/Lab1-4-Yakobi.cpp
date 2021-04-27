#include "libs.h"
#define M_PI 3.14159265358979323846


double errorPassed(vector<vector<double>> A, double eps, int n)
{
	double sum = 0;
	for (int i = 0; i < n; ++i)
	{
		for (int j = i + 1; j < n; ++j)
				sum += pow(A[i][j], 2);
	}

	double eps_k = sqrt(sum);
	cout << fixed << setprecision(5) << eps_k;
	if (eps_k <= eps)
		return true;
	else
		return false;	
}

double proisv(vector<double> a, vector <double> b, int n)
{
	double c = 0;
	for (int i = 0; i < n; ++i)
		c += a[i] * b[i];
	return c;	
}


double get_phi(vector<vector<double>> Aprev, int l, int m)
{
	double phi = 0;
	if (Aprev[l][l] != Aprev[m][m])
		phi = atan(2 * Aprev[l][m] / (Aprev[l][l] - Aprev[m][m])) / 2;
	else
		phi = M_PI / 4;
	
	return phi;
}

vector<vector<double>> Matrix(vector<vector<double>> Aprev, int n)
{
	vector <vector <double>> U;
	U.resize(n);
	for (int i = 0; i < n; ++i)
	{
		U[i].resize(n, 0);
	}

	for (int i = 0; i < n; ++i)
	{
		U[i][i] = 1;

	}

	int l = 0;
	int m = 1;
	double max = abs(Aprev[0][1]);
	for (int i = 0; i < n; ++i)
	{
		for (int j = i; j < n; ++j)
		{
			if (i != j)
			{
				if (abs(Aprev[i][j]) > max)
				{
					max = abs(Aprev[i][j]);
					l = i;
					m = j;
				}
			}
		}
	}

	cout << "Max = " << max << endl;
	cout << "l = " << l << " ;	m = " << m << endl;

	double phi = get_phi(Aprev, l, m);
	cout << "Phi = " << phi << endl;

	U[l][m] = -sin(phi);
	U[m][l] = sin(phi);
	U[l][l] = cos(phi);
	U[m][m] = cos(phi);

	return U;

}

vector<vector<double>> Yakobi(vector <vector <double>> A, vector <vector <double>> Aprev, vector <vector <double>> Uprev, vector <vector <double>> SV, int n, int k, double eps)
{
	
	Uprev = Matrix(Aprev, n);
	cout << "U(" << k << ")  = " << endl;
	show(Uprev, n);
	SV = proisv(SV, Uprev, n);

	A = proisv(proisv(transpose(Uprev, n), Aprev, n), Uprev, n);
	cout << "eps(" << k << ") = ";
	if (errorPassed(A, eps, n))
	{
		cout << " <= " << eps << endl << "Решение найдено на шаге " << k << '.' << endl;
		cout << "A:" << endl;
		show(A, n);
		cout << "Собственные значения:" << endl;
		cout << "lambda(1) = " << A[0][0] << "; lambda(1) = " << A[1][1] << "; lambda(1) = " << A[2][2] << "; " << endl;
		//SV = proisv(SV, Uprev, n);
		cout << endl;
		cout << "Матрица собственных векторов:" << endl;
		show(SV, n);
		vector <double> h1, h2, h3;
		h1.resize(n, 0);
		h2.resize(n, 0);
		h3.resize(n, 0);

		for (int i = 0; i < n; ++i)
			h1[i] = SV[i][0];
		for (int i = 0; i < n; ++i)
			h2[i] = SV[i][1];
		for (int i = 0; i < n; ++i)
			h3[i] = SV[i][2];
		cout << "Собственные вектора:" << endl;
		cout << "h(1) = " << endl;
		show(h1, n);
		cout << "h(2) = " << endl;
		show(h2, n);
		cout << "h(3) = " << endl;
		show(h3, n);

		cout << "Проверка:" << endl;
		cout << "h(1)*h(2) = " << proisv(h1, h2, n) << "; h(1)*h(3) = " << proisv(h1, h3, n) << "; h(2)*h(3) = " << proisv(h2, h3, n) << "; " << endl;
		
		return A;
	}
	else
	{
		cout << " > " << eps << endl;
		Aprev = A;
		cout << "A(" << k+1 << ")  = " << endl;
		show(Aprev, n);
		//SV = proisv(SV, Uprev, n);
		return Yakobi(A, Aprev, Uprev, SV, n, k + 1, eps);
	}
}

void Yakobi_main()
{
	double eps;
	int n, k = 0;
	ifstream test("test4-Yakobi.txt");
	test >> eps >> n;
	cout << "Заданная точность: " << eps << endl;

	
	vector <vector <double>> A, Uprev, SV;

	A.resize(n);
	Uprev.resize(n);
	SV.resize(n);
	for (int i = 0; i < n; ++i)
	{
		A[i].resize(n, 0);
		Uprev[i].resize(n, 0);
		SV[i].resize(n, 0);
		for (int j = 0; j < n; ++j)
			test >> A[i][j];
	}
	for (int i = 0; i < n; ++i)
	{
		SV[i][i] = 1;

	}

	Yakobi(A, A, Uprev, SV, n, k, eps);
	test.close();
}