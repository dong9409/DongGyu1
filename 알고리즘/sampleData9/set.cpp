#include <bits/stdc++.h>

using namespace std;

void Print_set(int* set, int set_size){
	for(int i=0; i<set_size; i++){
		cout << set[i] << " ";
	}
	cout << endl;
}

int c = 0;

void recur(int* arr, int len, int *set ,int set_size, int L, int i){
	
	if (L == 0){
		Print_set(set, set_size);
		c = c + 1;
		return ;
	}
	else if(L < 0 || i == len)
		return ;
	
	if(L - arr[i] >= 0){
		set[set_size] = arr[i];
		recur(arr, len, set, set_size + 1, L - arr[i], i);
		recur(arr, len, set, set_size, L, i+1);
	}
}


int main(void){
	ifstream ifs("3.inp");
	ofstream ofs("tube.out");
	int L;
	int n;
	ifs >> L >> n;
	int* arr = new int[n];
	int* set = new int[1000];
	int set_size = 0;
	
	for(int i=0; i<n; ++i)
		ifs >> arr[i];
	
	recur(arr, n, set, set_size, L, 0);
	return 0;
}
