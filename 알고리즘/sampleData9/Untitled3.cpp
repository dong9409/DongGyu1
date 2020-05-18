#include <bits/stdc++.h>

//https://makefortune2.tistory.com/110
//https://mantdu.tistory.com/746

using namespace std;

int recur(int L, int n, int* arr) {
	cout << L << ' ' << n << endl;
	if(n==1) {
		if(L % arr[0] == 0){
			cout << "find!" << endl;
			return 1;
		}
		else
			return 0;
	}
	
	int q = L/arr[n-1];
	int c=0;
	
	for(int i=0; i<=q; ++i){
		c += recur(L-i*arr[n-1], n-1, arr);
	}
	cout << n <<' ' << L << ' ' << c << endl;
	
	
	return c;
}

int main(void){
	ifstream ifs("1.inp");
	ofstream ofs("1t.out");
	int L;
	int n;
	ifs >> L >> n;
	int* arr = new int[n];
	
	for(int i=0; i<n; ++i)
		ifs >> arr[i];
	
	int ans = recur(L, n, arr);
	cout << ans << endl;
	return 0;
}
