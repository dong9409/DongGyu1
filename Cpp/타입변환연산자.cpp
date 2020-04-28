#include <iostream>

using namespace std;

class Point
{
	int x;
	int y;
public:
	explicit Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
	void Print() const { cout << x << ',' << y << endl; }
	operator int(void) const { return x; }
	~Point(void) {}
};

int main(void)
{
	int n = 10;
	
	Point pt(2, 3);
	n = pt; // n = pt 에서 pt를 n의 형식으로 타입변환한다. int 호출
	 
	cout << n << endl;
	return 0;
} 
