#include "libs.h"

double function(double b)
{
	double f = 0;
	f = 1 / (pow(b, 4) + 16);
	return f;
}

double func_doub_d(double b)
{
	double f = 0; 
	f = 32 * pow(b, 6) / pow((pow(b, 4) + 16), 3) - 12 * pow(b, 2) / pow((pow(b, 4) + 16), 2);
	return f;
}

double func_fourth_d(double b)
{
	double f = 0;
	f = 24 * 16 * 16 * pow(b, 12)*pow(b*b*b*b + 16, -5) - 24 * 16 * 9 * pow(b, 8)*pow(b*b*b*b + 16, -4) - 12 * 16 * 12 * pow(b, 5)*pow(b*b*b*b + 16, -4) + 16 * 10 * 6 * b*b*b*b*pow(b*b*b*b + 16, -3) + 48 * 4 * b*b*b*b*pow(b*b*b*b + 16, -3) - 24 * pow(b*b*b*b + 16, -2) + 24 * 20 * pow(b, 4)*pow(b*b*b*b + 16, -3) - 12 * 24 * 5 * pow(b, 8)*pow(b*b*b*b + 16, -4);
	return f;
}

double Runge_Romb_Rich(double F_h, double F_kh, int p)
{
	double RRR = 0;
	RRR = F_h + ((F_h - F_kh) / (pow(2, p) - 1));
	return RRR;
}

vector<double> rectangle(vector<double> x, vector<double> y, int n, double h)
{
	vector<double> F;
	F.resize(n + 1, 0);

	for (int i = 1; i < n + 1; ++i)
		F[i] = h*function(((x[i - 1] + x[i]) / 2)) + F[i - 1];
		
	double R = 0;
	double M = func_doub_d(x[0]);
	for (int i =0; i < n + 1; ++i)
	{
		if (func_doub_d(x[i])> M)
			M = func_doub_d(x[i]);
	}

	R = 2*pow(h, 2)*M / 24;

	for (int i = 0; i < n + 1; ++i)
		cout << "F(" << i << ") = " << F[i] << endl;

	cout << "Оценка остаточного члена R = " << R << endl;
	
	//cout << "Уточнённое значение (метод Рунге-Ромберга-Ричардсона) " << Runge_Romb_Rich(F_toch, F[n], n, h) << endl;
	//cout << "с абсолютной погрешностью " << abs(F_toch - Runge_Romb_Rich(F_toch, F[n], n, h)) << ". Точное значение интеграла " << F_toch << endl;
	return F;
	
}



vector<double> trapezium( vector<double> x, vector<double> y, int n, double h)
{
	vector<double> F;
	F.resize(n + 1, 0);
	for (int i = 1; i < n + 1; ++i)
	{
		if (i == 1 )
			F[i] = h*(function(x[i - 1]) / 2 + function(x[i])) + F[i - 1];
		else
			F[i] = h*(function(x[i])) + F[i - 1];
		if (i == n)
			F[i] = h*(function(x[i]) / 2) + F[i - 1];
	}

	double R = 0;
	double M = func_doub_d(x[0]);
	for (int i = 0; i < n + 1; ++i)
	{
		if (func_doub_d(x[i])> M)
			M = func_doub_d(x[i]);
	}

	R = 2 * pow(h, 2)*M / 12;

	for (int i = 0; i < n + 1; ++i)
		cout << "F(" << i << ") = " << F[i] << endl;

	cout << "Оценка остаточного члена R = " << R << endl;
	//cout << "Уточнённое значение (метод Рунге-Ромберга-Ричардсона) " << Runge_Romb_Rich(F_toch, F[n], n, h) << endl;
	//cout << "с абсолютной погрешностью " << abs(F_toch - Runge_Romb_Rich(F_toch, F[n], n, h)) << ". Точное значение интеграла " << F_toch << endl;
	return F;
}

vector<double> simpson(vector<double> x, vector<double> y, int n, double h)
{
	vector<double> F;
	F.resize(n + 1, 0);
	F[1] = h*(function(x[0]) + 4 * function(x[1])) / 3;
	for (int i = 2; i < n + 1; ++i)
	{
		if (i % 2 != 0 )
			F[i] = h*(4*function(x[i]))/3 + F[i - 1];
		else
			F[i] = h*(2*function(x[i]))/3 + F[i - 1];
		if (i == n)
			F[i] = h*(function(x[i])) / 3 + F[i - 1];
	}

	double R = 0;
	double M = func_fourth_d(x[0]);
	for (int i = 0; i < n + 1; ++i)
	{
		if (func_fourth_d(x[i])> M)
			M = func_fourth_d(x[i]);
	}

	R = 2 * pow(h, 4)*M / 180;
		
	for (int i = 0; i < n + 1; ++i)
		cout << "F(" << i << ") = " << F[i] << endl;
	cout << "Оценка остаточного члена R = " << R << endl;
	//cout << "Уточнённое значение (метод Рунге-Ромберга-Ричардсона) " << Runge_Romb_Rich(F_toch, F[n], n, h) << endl;
	//cout << "с абсолютной погрешностью " << abs(F_toch - Runge_Romb_Rich(F_toch, F[n], n, h)) << ". Точное значение интеграла " << F_toch << endl;
	return F;
}


void Integr_main()
{
	double x0 = 0;
	double x1=2;
	double h1 = 0.5;
	double h2 = 0.25;
	double F_toch = 0.108372;
	int n = 4;
	int N1 = 8;
	//n = (abs(x0) + abs(x1)) / h1;
	//N = (abs(x0) + abs(x1)) / h2;

	vector <double> x, y, F_rkh, F_tkh, F_skh ;
	x.resize(n+1, 0);
	y.resize(n+1, 0);
	F_rkh.resize(n + 1, 0);
	F_tkh.resize(n + 1, 0);
	F_skh.resize(n + 1, 0);

	for (int i = 1; i < n+1; ++i)
		x[i] = x0 + h1 + x[i-1];

	vector <double> x2, y2, F_rh, F_th, F_sh;
	x2.resize(N1 + 1, 0);
	y2.resize(N1 + 1, 0);
	F_rh.resize(N1 + 1, 0);
	F_th.resize(N1 + 1, 0);
	F_sh.resize(N1 + 1, 0);

	for (int i = 1; i < N1+1; ++i)
		x2[i] = x0 + h2 + x2[i-1];
		
	cout << "Вычисление определённого интеграла с шагом 0.5" << endl;
	cout << "Метод прямоугольников с шагом 0.5" << endl;
	//rectangle(x, y, n, h1);
	F_rkh = rectangle(x, y, n, h1);
	double f_rkh = F_rkh[n];
	cout << "Метод прямоугольников с шагом 0.25" << endl;
	//rectangle(x2, y2, N1, h2);
	F_rh = rectangle(x2, y2, N1, h2);
	double f_rh = F_rh[N1];

	cout << "Уточнённое значение (метод Рунге-Ромберга-Ричардсона) " << Runge_Romb_Rich(f_rh,f_rkh,2) << endl;
	cout << "с абсолютной погрешностью " << fixed << setprecision(8) << abs(F_toch - Runge_Romb_Rich(f_rh, f_rkh, 2)) << ". Точное значение интеграла " << F_toch << endl;
	cout << "_____________________________________________________________________________" << endl;
	cout << endl;
	cout << "Метод трапеций с шагом 0.5" << endl;
	//trapezium(x, y, n, h1);
	F_tkh = trapezium(x, y, n, h1);
	double f_tkh = F_tkh[n];
	cout << "Мeтод трапеций с шагом 0.25" << endl;
	//trapezium(x2, y2, N1, h2);
	F_th = trapezium(x2, y2, N1, h2);
	double f_th = F_th[N1];
	cout << "Уточнённое значение (метод Рунге-Ромберга-Ричардсона) " << Runge_Romb_Rich(f_th, f_tkh, 2) << endl;
	cout << "с абсолютной погрешностью " << fixed << setprecision(8) << abs(F_toch - Runge_Romb_Rich(f_th, f_tkh, 2)) << ". Точное значение интеграла " << F_toch << endl;
	cout << "_____________________________________________________________________________" << endl;
	cout << endl;
	cout << "Метод симпсона с шагом 0.5" << endl;
	//simpson(x, y, n, h1);
	F_skh = simpson(x, y, n, h1);
	double f_skh = F_skh[n];
	cout << "Метод Симпсона с шагом 0.25" << endl;
	simpson(x2, y2, N1, h2);
	F_sh = simpson(x2, y2, N1, h2);
	double f_sh = F_sh[N1];
	cout << "Уточнённое значение (метод Рунге-Ромберга-Ричардсона) " << Runge_Romb_Rich(f_sh, f_skh, 3) << endl;
	cout << "с абсолютной погрешностью " << fixed << setprecision(8) << abs(F_toch - Runge_Romb_Rich(f_sh, f_skh, 3)) << ". Точное значение интеграла " << F_toch << endl;

	cout << endl;
}