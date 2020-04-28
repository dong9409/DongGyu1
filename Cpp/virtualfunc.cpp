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

/*���������� private�� �ϸ� Base�� �����Ҽ� ���ٰ� �� 
�ֳ��ϸ� Base* b = new Derived1 ����  Derived1 �����Ͱ� Base*�� �ٲ��.
b�� Ȱ���ϰ� �Ǹ� Derived1 �޸� �߿��� BaseŬ������ �ش��ϴ� �޸𸮸� 
�ǵ帮�� �Ǵµ� �׷����ϸ� private�� ���� �ƴ���. 
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
