#include <iostream>

using namespace std;

class A{
public:
	A(){};
	~A(){};
	void m(){
		cout << "Method of A" << endl;
		b.m();
		c.m();
	}

	class B{
	public:
		B(){};
		~B(){};
		void m(){
			cout << "Method of B" << endl;
			d.m();
		}

		class D{
		private:
			int d;
		public:
			D(){ d = 0; };
			~D(){};
			void m(){
				d++;
				cout << "Method of D(" << d << ")" << endl;
			}
		};
	private:
		D d;
	};

	class C{
	public:
		C(){};
		~C(){};
		void m(){
			cout << "Method of C" << endl;
			j.m();
			e.m();
		}
		class J {
		
		public:
			J(){};
			~J(){};
			void m(){
				k.m();
				cout << "Method of J" << endl;
			}
			class K{
			private: int k;
			public:
				K(){ k = 0; };
				~K(){};
				void m(){
					k++;
					cout << "Method of K(" << k << ")" << endl;
				}
			};
		private:
			K k;
			
		};

		class E{
		private: int e;
		public:
			E(){ e = 0; };
			~E(){};
			void m(){
				e++;
				cout << "Method of E(" << e << ")" << endl;
			}
		};
	private:
		E e;
		J j;
	};

private:
	B b;
	C c;
};

int main()
{
	A a;
	A::B b; // отдельный объект B, не содержащий элементы A, C, E, J, K
	b.m();
	cout << endl;

	a.m();
	cout << endl;

	
	A::C c; // отдельный объект С, не содержащий элементы A, B, D

	c.m();
	cout << endl;

	a.m();
	cout << endl;

	return 0;
}