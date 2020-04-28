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
	
	pt = 10; // ���� ���Ͱ����� x�� 10 y�� 0�� �ִ� �����ڰ� ȣ��ȴ�.
	pt.Print(); 
	return 0;
} 
