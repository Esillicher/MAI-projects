#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;

void SphereDecartPoint(float a, float b)
{
	float R = 5.0;
	float x0 = 0;
	float y0 = 0;
	float z0 = R;
	cout << R * cos(a)*cos(b) + x0 << " " << R * sin(b) + y0 << " " << R * sin(a)*cos(b) + z0 << " ";
}

int main()
{
	freopen ("../raw/sphere.raw", "w", stdout);
	cout << fixed << setprecision (4);
	float da = M_PI / 20.0;

	for (float a = -M_PI; a < M_PI ; a += da)
    {
        for (float b = -M_PI/2; b < M_PI/2; b += da)
        {
        	float aa = a + da;
            float bb = b + da;

            SphereDecartPoint(a, b);
            SphereDecartPoint(a, bb);
            SphereDecartPoint(aa, b);
            cout << endl;
            SphereDecartPoint(a, bb);
            SphereDecartPoint(aa, bb);
            SphereDecartPoint(aa, b);
            cout << endl;
        }
    }

	return 0;
}
