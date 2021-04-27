#include "libs.h"

vector<double> Vsum(vector<double> a, vector<double> b)
{
	vector<double> sum;
	sum.resize(a.size(), 0);
	for (unsigned int i = 0; i < a.size(); ++i)
		sum[i] = a[i] + b[i];
	return sum;
}

vector<double> Vdiff(vector<double> a, vector<double> b)
{
	vector<double> diff;
	diff.resize(a.size(), 0);
	for (unsigned int i = 0; i < a.size(); ++i)
		diff[i] = a[i] - b[i];
	return diff;
}

vector<double> proisv(vector <vector <double>> A, vector <double> B, int n)
{
	vector<double> R;
	R.resize(n,0);

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
				R[i] += A[i][j] * B[j];
	return R;
}

double norm(vector<double> v, int n)
{
	double sum = 0;
	for (int i = 0; i < n; ++i)
		sum += v[i] * v[i];
	return sqrt(sum);
}

double norm(vector<vector<double>> M, int n)
{
	double sum = 0;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
		sum += M[i][j] * M[i][j];
	return sqrt(sum);
}

vector<vector<double>> get_alpha(vector<vector<double>> A, int n)
{
	vector<vector<double>> alpha;
	alpha.resize(n);
	for (int i = 0; i < n; ++i)
	{
		alpha[i].resize(n, 0);
		for (int j = 0; j < n; ++j)
		{
			if (i != j) alpha[i][j] = -A[i][j] / A[i][i];
			else alpha[i][j] = 0;
		}
	}
	return alpha;
}

vector<double> get_beta(vector<vector<double>> A, vector<double>B, int n)
{
	vector<double> beta;
	beta.resize(n, 0);
	for (int i = 0; i < n; ++i)
		beta[i] = B[i] / A[i][i];
	return beta;
}

bool errorPassed(vector<vector<double>> alpha, vector<double> x_diff, double eps, int n)
{
	double eps_k = norm(alpha, n) * norm(x_diff, n) / (1 - norm(alpha, n));
	cout << fixed << setprecision(5) << eps_k;
	if ( eps_k <= eps)
		return true;
	else
		return false;
}

vector<double> SimpleIteration(vector<double> x, vector<vector<double>> alpha, vector<double> beta, double eps, int k, int n)
{
	if (k == 0)
		return SimpleIteration(x, alpha, beta, eps, k + 1, n);
	
	vector<double> new_x = Vsum(beta, proisv(alpha, x, n));
	cout << "eps(" << k << ") = ";
	if (errorPassed(alpha, Vdiff(new_x, x), eps, n))
	{
		cout << " <= " << eps << endl << "Решение найдено на шаге " << k << '.' << endl << "X:" << endl;
		return new_x;
	}
	else
	{
		cout << " > " << eps << endl;
		return SimpleIteration(new_x, alpha, beta, eps, k + 1, n);
	}
}

double Zeidel_xk(vector<vector<double>> alpha, vector<double> beta,
	vector<double> x, vector<double> x_prev, int i, int n)
{
	double xk = beta[i];
	for (int j = 0; j < i; ++j)
		xk += alpha[i][j] * x[j];

	for (int j = i; j < n; ++j)
		xk += alpha[i][j] * x_prev[j];

	return xk;
}

vector<double> Zeidel(vector<vector<double>> alpha, vector<double> beta, double eps, int n)
{
	vector<double> x, x_prev = beta;
	int count = 1;
	x.resize(n, 0);
	
	for (int i = 0; i < n; ++i)
		x[i] = Zeidel_xk(alpha, beta, x, x_prev, i, n);

	cout << "eps(1) = ";
	while (!errorPassed(alpha, Vdiff(x, x_prev), eps, n))
	{
		cout << endl;
		x_prev = x;
		for (int i = 0; i < n; ++i)
			x[i] = Zeidel_xk(alpha, beta, x, x_prev, i, n);

		cout << "eps(" << ++count << ") = ";
	}
	cout << " <= " << eps << endl << "Решение найдено на шаге " << count << '.' << endl << "X:" << endl;

	return x;
}

void SimpleIteration_main()
{
	double eps;
	int n;
	ifstream test("test3-SimpleIteration.txt");
	test >> eps >> n;
	cout << "Заданная точность: " << eps << endl;

	vector <vector <double>> A, alpha;
	vector <double> b, beta;
	A.resize(n);
	b.resize(n);
	for (int i = 0; i < n; ++i)
	{
		A[i].resize(n, 0);
		for (int j = 0; j < n; ++j)
			test >> A[i][j];

		test >> b[i];
	}
	cout << "Исходная матрица коэффициентов:" << endl;
	show(A, n);

	alpha = get_alpha(A, n);
	beta = get_beta(A, b, n);

	if (norm(alpha, n) < 1)
	{
		cout << "Решение методом простых итераций." << endl;
		show(SimpleIteration(beta, alpha, beta, eps, 0, n), n);
		cout << endl;

		cout << "Решение методом Зейделя." << endl;
		show(Zeidel(alpha, beta, eps, n), n);
		cout << endl;
	}
	else
		cout << "Норма матрицы эквивалентной системы >= 1, решений нет." << endl << endl;

	test.close();
}