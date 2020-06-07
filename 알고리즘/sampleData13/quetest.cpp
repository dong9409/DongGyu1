#include <iostream>
#include <queue>

using namespace std;

class test{
public:
	int a=0;
};
test t1;
int main(void){
	test q;
	t1.a = 1;
	queue<test> que;
	que.push(t1);
	cout << que.front().a << endl;
	t1.a = 2;
	que.push(t1);
	que.pop();
	cout << que.front().a << endl;
	return 0;
}
