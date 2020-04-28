#include <iostream>

using namespace std;

class Base
{
public:
	int x;
public:
	Base(int _x=0): x(_x) {}
	virtual void SimpleFunc()
	{
		cout << "base" << endl;
	}
};

/*접근지정자 private로 하면 Base로 접근할수 없다고 함 
왜냐하면 Base* b = new Derived1 에서  Derived1 포인터가 Base*로 바뀐다.
b를 활용하게 되면 Derived1 메모리 중에서 Base클래스에 해당하는 메모리를 
건드리게 되는데 그렇게하면 private에 의해 컷당함. 
*/
 
class Derived1:public Base
{
public:
	Derived1(int _x=0): Base(_x){}
	
	void SimpleFunc()
	{
		cout << "derived1" << endl;
	}
};

class Derived2:public Derived1
{
public:
	Derived2(int _x=0): Derived1(_x){}
	void SimpleFunc()
	{
		cout << "derived2" << endl;
	}
};


int main()
{
	Base* b = new Derived1;
	Derived1* d1 = new Derived2;
	b->SimpleFunc();
	d1->SimpleFunc();
	
	
	return 0;
}
