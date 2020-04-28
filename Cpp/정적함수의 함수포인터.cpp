#include <iostream>

using namespace std;

void Print(int n)
{
	cout << "전역함수: " << n << endl;
}

namespace A
{
	void Print(int n)
	{
		cout << "namespace A 전역함수: " << n << endl;
	}
}

class Point
{
public:
	static void Print(int n)
	{
		cout << "Point 클래스의 정적 멤버 함수: " << n << endl;
	}
};

//정적함수 포인터는  void (*pf)(int)로 같다
 
int main(void)
{
	void (*pf)(int);
	
	Print(10);
	A::Print(10);
	Point::Print(10);
	
	pf = Print;
	pf(10);
	pf = A::Print;
	pf(10);
	pf = Point::Print;
	pf(10);
	
	return 0;	
}
