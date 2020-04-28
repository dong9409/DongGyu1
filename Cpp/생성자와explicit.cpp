#include <iostream>

using namespace std;

class Point
{
	int x;
	int y;
public:
	explicit Point(int _x = 0 , int _y = 0):x(_x), y(_y) { }
	void Print() const { cout << x << ',' << y << endl; }
};

int main(void)
{
	Point pt;
	pt.Print();
	
	//pt = 10; 생성자를 통한 형변환을 하기 싫으면 explicit 키워드를 적는다.
	pt = 10; 
	pt = Point(10); //명시적 호출만 가능하다. 
	pt.Print(); 
	return 0;
} 
