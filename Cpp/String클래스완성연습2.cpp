#include <iostream>

using namespace std;

class String{
	const char* ptr;
public:
	String(const char* s){
		ptr = new char[10];
		ptr = s;
	}
	void print(void) const { cout << ptr << endl; }
	~String(void) { delete [] ptr; }
};
int main(void)
{
	const char* sz = "Hello!";
	String s("Hi~!");
	s = sz;
	return 0;
}


/* ����
	const char* sz = "Hello!";
	String s("Hi~!");
	s = sz;
	�� ������ �ǵ��� �ּ����� String Ŭ������ �����ϼ��� 
*/ 
