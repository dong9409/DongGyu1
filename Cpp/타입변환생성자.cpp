#include <iostream>

using namespace std;

class test1
{	
};

class test
{
};
 
class test2
{
public:
	test2(void) { cout << "test() ������" << endl; }
	test2(test1& t) {cout << "test2(test1& t) ������" << endl;}
	test2(int n) {cout << "test2(int n) ������" << endl;}
	test2(double d) { cout << "test2(double d) ������" << endl;}
};

int main(void)
{
	test1 t1;
	test t;
	int n = 10;
	double d = 5.5;
	
	test2 t2;
	t2 = t1; // t2 = test2(t1); ���Կ����ڰ� ������ó�� �ۿ��Ѵ�. 
	t2 = n; // t2 = test2(n);
	t2 = d; // t2 = test2(d);
	t2 = test2(t1);
	// t2 = t; test Ŭ������ �̿��ϴ� �����ڰ� �����Ƿ� ����  
	return 0;
}
