#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;


int main(void)
{
	int arr[5] = {1, 2, 3, 4, 1};
	int* p = min_element(arr+5, arr);
	cout << p << ' ' << &arr[0] << endl;
	return 0;
}
