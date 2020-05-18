#include <bits/stdc++.h>

using namespace std;

void Print_set(int* set, int set_size){
	for(int i=0; i<set_size; i++){
		cout << set[i] << " ";
	}
	cout << endl;
}

ifstream ifs("tube.inp");
ofstream ofs("tube.out");

vector<int> size = {999999};

int c=0;
void recur(int* arr, int len, int *set ,int set_size, int L, int i){
	c=c+1;
	if (L == 0){
		size.push_back(set_size);
		return ;
	}
	else if(L < 0 || i < 0 || set_size >= *min_element(size.begin(), size.end()))
		return ;
	
	if(L - arr[i] >= 0){
		set[set_size] = arr[i];
		recur(arr, len, set, set_size + 1, L - arr[i], i);
		recur(arr, len, set, set_size, L, i-1);
	}
}


int main(void){
	int L;
	int n;
	ifs >> L >> n;
	int* arr = new int[n];
	int* set = new int[10000];
	int set_size = 0;
	
	for(int i=0; i<n; ++i)
		ifs >> arr[i];
	
	recur(arr, n, set, set_size, L, n-1);
	ofs << *min_element(size.begin(), size.end());
	return 0;
}
