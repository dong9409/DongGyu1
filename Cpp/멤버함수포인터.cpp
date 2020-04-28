#include <iostream>

using namespace std;

class Point
{
	int x;
	int y;
public:
	explicit Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
	void Print() const {cout << x << ',' << y << endl;}
	void PrintInt(int n) {cout << "테스트 정수 : " << n << endl;}
};

int main(void)
{
	Point pt(2, 3);
	Point *p = &pt;
	
	void (Point::*pf1) (void) const;
	pf1 = &Point::Print;
	
	void (Point::*pf2) (int);
	pf2 = &Point::PrintInt;
	
	pt.Print();
	pt.PrintInt(10);
	cout << endl;
	
	(pt.*pf1) ();
	(pt.*pf2) (10);
	cout << endl;
	
	(p->*pf1) ();
	(p->*pf2) (10);
	
	//pf1이 Point클래스 안에있는 Print를 가리키는데 *pf1은 Print니까 이렇게씀 
	return 0;
}
