#include <iostream>

using namespace std;

class test{
	int x;
	int y;
public:
	test(int _x = 0, int _y = 0): x(_x), y(_y) {}
	void set(int a, int b){
		x = a, y = b;
	}
	void print(void)const{
		cout << x <<',' << y << endl;
	}
};
int main(void)
{
	test t1;
	test t2(1, 2);
	t1.print();
	t2.print();
	t1 = t2;
	t1.print();
	t2.print();
	return 0;
}
