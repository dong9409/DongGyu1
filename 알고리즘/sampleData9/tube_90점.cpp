#include <bits/stdc++.h>

using namespace std;

int min_i(int* mod, int len){
	int min = mod[0];
	int min_index;
	
	for(int i=0; i<len; ++i){
		if(mod[i] <= min){
			min = mod[i];
			min_index = i;
		}
	}
	return min_index;
}

int main(void){
	ifstream ifs("tube.inp");
	ofstream ofs("tube.out");
	int L;
	int n;
	ifs >> L >> n;
	int* arr = new int[n];
	int* mod = new int[n];
	
	for(int i=0; i<n; ++i){
		ifs >> arr[i];
		mod[i] = 0;
	}
	int ans=0;
	
	while(L>0){
		for(int i=0; i<n; ++i){
			mod[i] = L % arr[i];
		}
		L = L -arr[min_i(mod, n)];
		ans ++;
	}
	if(L==0)
		ofs << ans;
	else
		ofs << 0;
	return 0;
}
