#include <iostream>

using namespace std;

class test
{
	int x;
	int y;
public:
	test(int _x=1, int _y=0): x(_x), y(_y) {}
	void Print() const{
		cout << x << ',' << y << endl;
	}
};
int main(void)
{
	test().Print();
	return 0;
}
