#include <iostream>

using namespace std;

class String{
	const char* ptr;
public:
	String(const char* s){
		ptr = new char[10];
		ptr = s;
	}
	operator const char*(void) {
		return ptr;
	}
	void print(void) const { cout << ptr << endl; }
};
int main(void)
{
	String s("Hello!");
	const char* sz = s;	
	s.print();
	cout << sz << endl;
	return 0;
}


/* ����
	String s("Hello!");
	const char* sz = s; �� ������ �ǵ��� String �� �ۼ��ϼ���
*/ 
