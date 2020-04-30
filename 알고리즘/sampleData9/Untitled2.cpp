#include <bits/stdc++.h>

//https://makefortune2.tistory.com/110
//https://mantdu.tistory.com/746

using namespace std;

int table[10][100000];
static int i;

int recur(int L, int n, int* arr, vector<int> v) {
	v.push_back(arr[n-1]);
	if(n==1) {
		if(L % arr[0] == 0){
			v.push_back(L % arr[0]);
			cout << "find!" << ' ';
			for(auto it=v.begin(); it!=v.end(); ++it)
				cout << (*it) << ' ';
			cout << endl;
			return 1;
		}
		else
			return 0;
	}
	if(table[n][L] != 0)
		return table[n][L];
	
	int q = L/arr[n-1];
	int c=0;
	
	for(int i=0; i<=q; ++i){
		c += recur(L-i*arr[n-1], n-1, arr, v);
	}
	cout << n <<' ' << L << ' ' << c << endl;
	
	table[n][L] = c;
	
	return c;
}

int main(void){
	ifstream ifs("test1.inp");
	ofstream ofs("1t.out");
	int L;
	int n;
	ifs >> L >> n;
	int* arr = new int[n];
	vector<int> v;
	
	for(int i=0; i<n; ++i)
		ifs >> arr[i];
	
	int ans = recur(L, n, arr, v);
	cout << ans << endl;
	return 0;
}
