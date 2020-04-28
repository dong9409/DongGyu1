#include <iostream>

using namespace std;

class A
{
};

class B
{
public:
	operator A()
	{
		cout << "operator A()" << endl;
		return A();
	}
	
	operator char()
	{
		cout << "operator char()" << endl;
		return 'c';
	}
	operator double()
	{
		cout << "opeator double()" << endl;
		return 10.0; 
	}
};

int main(void)
{
	char n;
	double d;
	B b;
	
	n = char(b);
	d = double(b);
	cout << n << endl;
	cout << d << endl;
	return 0;
}
