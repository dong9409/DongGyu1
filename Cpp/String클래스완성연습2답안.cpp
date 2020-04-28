#include <iostream>
#include <cstring>

using namespace std;

class String
{
	char* buf;
public:
	String(const char* sz)
	{
		buf = new char[strlen(sz) + 1]; //���� Ȯ���� �Ѵ�. 
	}
	~String()
	{
		delete [] buf;
	}
	const String& operator=(const char* arg){ 
		//���� ����Ű�� �ִ°� ���� + ������ ����  
		delete [] buf;
		buf = new char[strlen(arg) + 1];
		strcpy(buf, arg);
		
		return *this;
	}
	void Print(void) const { cout << buf << endl; };
};  

int main(void)
{
	const char* sz = "Hello!";
	String s("Hi~!");
	s = sz;
	s.Print();
	return 0;
}
