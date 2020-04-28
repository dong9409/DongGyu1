#include <iostream>

using namespace std;

class Array
{
	int *arr;
	int sz;
	int capacity;

public:
	Array(int cap=100):arr(0), sz(0), capacity(cap) {
		arr = new int[capacity];
	}
	~Array()
	{
		delete [] arr;
	}
	Array& operator=(const Array& arg){
		delete [] arr;
		arr = new int[capacity];
	
		arr = arg.arr;
		sz = arg.sz;
		capacity = arg.capacity;
		
		return *this;
	}
	void print(void)const {
		for(int i=0 ; i < sz ; i++)
			cout << arr[i] << endl;
	}
	void Add(int data)
	{
		if(sz < capacity)
			arr[sz++] = data;
	}
	
	int Size() const {
		return sz;
	}
	
	int operator[] (int idx) const {
		return arr[idx];
	}
};

int main()
{
	Array ar(10);
	ar.Add(10);
	ar.Add(20);
	ar.Add(30);
	ar.print();
	Array ar1 = ar;
	ar1.print();
	return 0;
}
