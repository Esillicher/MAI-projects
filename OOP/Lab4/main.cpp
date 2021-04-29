#include <iostream>
#include <locale.h>
using namespace std;

class B;
class C;
class D;
class E;
class F;

// категория наследование: расширение
// принцип подстановки выполняется не полностью
class A{
public:
	A(){ a = 2; }
	virtual ~A(){	//замещаемый деструктор
		cout << "~A" << endl;
	}
	virtual int ma(){ // замещаемая функция
		cout << "Метод А = a = " << a << endl;
		return a;
	}
protected:
	int a;
};
class B : public A{
public:
	B(){ b = 20; }
	~B(){ cout << "~B" << endl; }
	int ma(){ // замещение
		cout << "Метод В (А) = а = " << a << endl;
		return a;
	}
	int mb(){ // расширение функциональных возможностей
		cout << "Метод В (В) = a*b = " << a*b << endl;
		return a*b;
	}
protected:
	int b; // расширение по данным
};

// категория наследование: специализация
class C:public A{
public:
	C(){ c = 30; }
	~C(){ cout << "~C" << endl; }
	int ma(){ //замещаемая функция класса A - со специализированным поведением
		c++; //изменяет состояние объекта
		cout << "Метод C (А) = с =" << c << "(c изменилось, ф-я со специализ. поведением)"<<endl;
		return c;
	}
protected:
	int c; // дополнительный атрибут
};

// категория наследование: спецификация
class D :public A{ // абстрактный класс. D - подкласс А, полная подстановка
public:
	D(){ d = 1; }
	~D(){ cout << "~D" << endl; }
	int ma() = 0;
protected:
	int d;
};

class E :public D{ // подкласс абстрактного класса D
public:
	E(){ e = 50; }
	~E(){ cout << "~E" << endl; }
	int ma(){
		cout << "Метод Е (А->D) = a*e = "<< a*e << endl;
		return a*e;
	}
private:
	int e;
};

//конструирование 
class F :public A{	//F - подкласс А
public:
	F(){ f = 7; }
	~F(){	//замещаемый деструктор
		cout << "~F" << endl;
	}
	int ma(int f) {
		cout << "a*f="<< a*f << endl;
		return a*f;//"замещаемая" функция с измененным аргументом
	}
	int mf() {
		//"замещаемая" функция с измененным именем
		cout << "Метод F(A) = f+a = " << A::ma() << a+f << endl;
		return a+f;
	}
private:
	int f;
};

int main(){
	setlocale(LC_ALL, "Rus");
	A *a; // a - полиморфный указатель
	B *b;

	cout << "\t\tНаследование: расширение" << endl;
	cout << "Создание объекта A:" << endl;
	a = new A;
	a->ma();
	cout << "Создание объекта B:" << endl;
	a = new B;// подстановка
	a->ma();
	b = dynamic_cast<B*>(a);
	b->mb();
	delete a;
	cout << endl << "a->mb(); неполное выполнение принципа подстановки. Метод mb класса B недоступен из a.\n" << endl;
	cout << "Создание объекта B:" << endl;
	b = new B();
	b->ma();
	b->mb();
	delete (A*) b;
	
	cout << endl << "\t\tНаследование: специализация" << endl;
	cout << "Создание объекта A:" << endl;
	a = new A;
	a->ma();
	cout << "Создание объекта С:" << endl;
	a = new C;
	a->ma();
	delete a;
	
	cout << endl << "\t\tНаследование: спецификация" << endl;
	cout << "Создание объекта A:" << endl;
	a = new A;
	a->ma();
	cout << endl << "!a = new D;	Нельзя создать экземпляр абстрактного класса!\n" << endl;
	cout << "Создание объекта E:" << endl;
	a = new E;
	a->ma();
	delete a;


	//конструировние
	cout << endl << "\t\tНаследование: конструирование" << endl;
	a = new F;
	a->ma();
	//a->mf();
	delete a;

	F *f;
	cout << endl << "!a->mf(); Невозможно: неполное замещение - mf не доступен из А!\n" << endl;
	f = new F;
	f->ma(9);
	f->mf();
	delete (A*)f;
	delete f;

	return 0;
}