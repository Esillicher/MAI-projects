#include <iostream>
#include <locale.h>
using namespace std;

class Parent_A
{
public:
	Parent_A(){ a = 5; }
	virtual ~Parent_A(){
		cout << "~A" << endl;
	}	//a1 - формальная перем. (аргумент конструктора)
	Parent_A(int a1){ a = a1; cout << "Parent_A(" << a << ")" << endl; }
	virtual int m(){
		cout << "m(Parent_A): a=" << a << endl;
		return a;
	}
	int get_a(){ return a; };
private:
	int a;
protected:
};

class Child1_B : virtual public Parent_A
{
public:
	Child1_B(){ b = 10; }
	Child1_B(int b1){
		b = b1; cout << "Child1_B(" << b << ")" << endl;
	}
	Child1_B(int b1, int a1) : Parent_A(a1){ b = b1; cout << "Child1_B("<<b<<")" << endl; }
	~Child1_B(){
		cout << endl << "~B" << endl;	}	
	int get_b(){ return b; };
	int m(){
		cout << "m(from child1_B): b*a=" << b*get_a() << endl;
		return b*get_a();
	}
private:
	int b;
protected:
};

class Child2_C : virtual public Parent_A
{
public:
	Child2_C(){ c = 15; }
	Child2_C(int c1){ c = c1; cout << "Child2_C(" << c << ")" << endl; }
	~Child2_C(){
		cout << "~C" << endl;	
	}
	int m(){
		cout << "m(from child_C): c*a=" << c*get_a() << endl;
		return c*get_a();
	}
	int get_c(){ return c; }
private:
	int c;
protected:
};
class GrandChild_D : public Child1_B, public Child2_C
{
public:
	GrandChild_D(){ d = 20; }
	GrandChild_D(int d1, int c1, int b1, int a1) :Child2_C(c1), Child1_B(b1), Parent_A(a1) {
		d = d1; 
		cout << "GrandChild_D(" << d << ")" << endl;
	}
	~GrandChild_D(){
		cout << "~D" << endl;
	}
	int m(){
		cout << "m(from GrandChild_D); d+c+b+a=" << d + get_c() + get_b() + get_a() << endl;
		return d + get_c() + get_b() + get_a();
	}
private:
	int d;
protected:
};

int main(){
	Parent_A *a;
	//выполнение принципа подстановки
	a = new Parent_A();
	a->m();
	delete a;
	cout<< endl;

	a = new Child1_B();
	a->m();
	delete a;
	cout << endl;

	a = new Child2_C();
	a->m();
	delete a;
	cout << endl;

	a = new GrandChild_D();
	a->m();
	delete a;
	cout << endl;
	
	Child1_B *b;
	b = new Child1_B(100, 200);
	b->m();
	delete b;
	cout << endl;

	b = new GrandChild_D(9, 8, 7, 6);
	b->m();
	delete b;
	cout << endl;

	b = new GrandChild_D;
	b->m();
	delete b;

}