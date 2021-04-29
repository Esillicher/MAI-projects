#include <iostream>

using namespace std;

class E;

class D{
public:
	D(){ i = 0; j = 0; }
	~D(){}
	void set_e(E &e)
	{
		if (i<3){
			cout << "attach E pos: " << &e << endl;
			pe[i] = &e;
			i++;
		}
	}
	E* get_next(){
		cout << "D->E[" << j << "]  ";
		//if (j < i) j++;
		return pe[j++];
	}
	void m(){
		cout << "method of D" << endl;
	};
private:
	int i, j;
	E *pe[3];
protected:
};

class E{
public:
	E(){}
	~E(){}
	void set_d(D &_d)
	{
		cout << "attach D pos: " << &_d << endl;
		d = &_d;
	}
	D* get_d(){
		cout << "D->E  ";
		return d;
	}
	void m(){
		cout << "method of E" << endl;
	};
private:
	D *d;
protected:
};

int main(){
	D d;
	E e1, e2, e3;

	d.set_e(e1);
	d.set_e(e2);
	d.set_e(e3);
	e1.set_d(d);
	e2.set_d(d);
	e3.set_d(d);


	e1.get_d()->m();
	e2.get_d()->m();
	e3.get_d()->m();

	for (int i = 0; i<3; i++)
	{
		d.get_next()->m();
	}

	char ch;
	cin >> ch;

	return 0;
}
