#include <iostream>
#include <cstring>

using namespace std;

class String
{
	char* buf;
public:
	String(const char* sz)
	{
		buf = new char[strlen(sz) + 1]; //공간 확보만 한다. 
	}
	~String()
	{
		delete [] buf;
	}
	const String& operator=(const char* arg){ 
		//현재 가리키고 있는거 해제 + 데이터 복사  
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
