#include <bits/stdc++.h>

//https://makefortune2.tistory.com/110
//https://mantdu.tistory.com/746

using namespace std;

int table[10][100000];

int recur(int L, int n, int* arr) {
	if(n==1) {
		if(L % arr[0] == 0){
			cout << L << ' ' << "find!" << endl;
			return 1;
		}
		else
			return 0;
	}
	cout << L  << endl;
	
	int q = L/arr[n-1];
	int c=0;
	
	for(int i=0; i<=q; ++i){
		c += recur(L-i*arr[n-1], n-1, arr);
	}
	
	
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
