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
	test2(void) { cout << "test() 생성자" << endl; }
	test2(test1& t) {cout << "test2(test1& t) 생성자" << endl;}
	test2(int n) {cout << "test2(int n) 생성자" << endl;}
	test2(double d) { cout << "test2(double d) 생성자" << endl;}
};

int main(void)
{
	test1 t1;
	test t;
	int n = 10;
	double d = 5.5;
	
	test2 t2;
	t2 = t1; // t2 = test2(t1); 대입연산자가 생성자처럼 작용한다. 
	t2 = n; // t2 = test2(n);
	t2 = d; // t2 = test2(d);
	t2 = test2(t1);
	// t2 = t; test 클래스를 이용하는 생서자가 없으므로 에러  
	return 0;
}
