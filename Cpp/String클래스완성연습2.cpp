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


/* 문제
	const char* sz = "Hello!";
	String s("Hi~!");
	s = sz;
	가 컴파일 되도록 최소한의 String 클래스를 설계하세요 
*/ 
