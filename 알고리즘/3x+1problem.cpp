#include <iostream>

using namespace std;

int main(void)
{
	int x;
	cin >> x;
	while(x>1)
	{
		if(x%2 == 0)
			x = x/2;
		else
			x = 3*x+1;
	}
	return 0;
}
