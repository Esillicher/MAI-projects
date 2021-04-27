#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>
#include <Windows.h>
using namespace std;
#pragma once

void LU_main();
void Tridiagonal_main();
void SimpleIteration_main();
void Yakobi_main();

void show(vector <vector <double>> A, int n);
void show(vector <double> x, int n);
double detA(vector <vector <double>> U, int n);
vector<vector<double>> transpose(vector <vector<double>> M, int n);
vector<vector<double>> proisv(vector <vector <double>> A, vector <vector <double>> B, int n);