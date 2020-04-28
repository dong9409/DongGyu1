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
	
	//pt = 10; �����ڸ� ���� ����ȯ�� �ϱ� ������ explicit Ű���带 ���´�.
	pt = 10; 
	pt = Point(10); //����� ȣ�⸸ �����ϴ�. 
	pt.Print(); 
	return 0;
} 
