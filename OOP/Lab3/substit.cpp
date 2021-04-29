#include <iostream>
#include <locale.h>
using namespace std;

// принцип подстановки
class A { // cуперкласс
public:
	A() {
		a = 0;
		cout << "A a=" << a << endl;
	}
	virtual ~A(){ cout << "~A" << endl; }
	virtual int Ma() { // virtual для замещения функции
		return a;
	}
protected:
	int a;
};

class B: public A { // подкласс
public:
	B() {
		a = 1;
		cout << "B a=" << a << endl;
	}
	~B(){ cout << "~B" << endl; }
	int Ma() { // замещение функции
		return a + 10;
	}
};

class C: public B { // подкласс
public:
	C() {
		a = 2;
		cout << "C a=" << a << endl;
	}
	~C(){ cout << "~C" << endl; }
	int Ma() { // замещение функции
		return a + 100;
	}
};

class D: public C { // подкласс
public:
	D() {
		a = 3;
		cout << "D a=" << a << endl;
	}
	~D(){ cout << "~D" << endl; }
	int Ma() { // замещение функции
		return a + 1000;
	}
};

int main() {
	setlocale(LC_ALL, "Rus");

	A *a; // а — полиморфная переменная (указатель,ссылка)
	cout << "Создание объекта A:" << endl;
	a = new A;
	cout << a->Ma() << endl;
	delete a; // удаление объекта

	cout << endl << "Создание объекта B:" << endl;
	a = new B;
	cout << a->Ma() << endl; // полиморфный вызов
	delete a; // если конструктор не virtual

	cout << endl << "Создание объекта C:" << endl;
	a = new C;
	cout << a->Ma() << endl;
	delete a;

	cout << endl << "Cоздание объекта D" << endl;
	a = new D;
	cout << a->Ma() << endl;
	// D* d = dynamic_cast <D*> (a); // преобразование указателя
	// if (d != NULL){
	if (dynamic_cast <D*> (a) != NULL) {
		cout << " по указателю объект D " << endl;
	}
	delete a;

	cout << endl << "Проход по массиву с условием:" << endl;
	A *mas[4];
	mas[0] = new A;
	mas[1] = new B;
	mas[2] = new C;
	mas[3] = new D;
	for (int i = 0; i < 4; ++i)
	{
		if (dynamic_cast <A*> (mas[i]) != NULL &&
			dynamic_cast <B*> (mas[i]) == NULL &&
			dynamic_cast <C*> (mas[i]) == NULL &&
			dynamic_cast <D*> (mas[i]) == NULL ||
			dynamic_cast <C*> (mas[i]) != NULL &&
			dynamic_cast <D*> (mas[i]) == NULL)
			cout << "Условие верно для элемента " << i << endl;
	}

	for (int i = 0; i < 4; ++i)
		delete mas[i];

	//getchar();
	return 0;
}