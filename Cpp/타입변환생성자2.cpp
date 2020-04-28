#include <iostream>

using namespace std;

class Point
{
	int x;
	int y;
public:
	Point(int _x = 0 , int _y = 0):x(_x), y(_y) { }
	void Print() const { cout << x << ',' << y << endl; }
};

int main(void)
{
	Point pt;
	pt.Print();
	
	pt = 10; // 에러 날것같지만 x에 10 y에 0을 넣는 생성자가 호출된다.
	pt.Print(); 
	return 0;
} 
