#include <bits/stdc++.h>

using namespace std;


int main(void){
	ifstream ifs("allin.inp");
	ofstream ofs("allin.out");
	int i = 0;
	int j = 0;
	int sz;
	short* arr;
	ifs >> sz;
	arr = new short[sz];
	while(ifs>>arr[i])
		i++;
	
	int start = 0;
	int max_index;
	int min_index;
	
	short min = *min_element(&arr[start], arr+sz);
	short ans=0;
	int b;
	int s;
	
	
	while(start < sz-1){
		max_index = max_element(&arr[start], arr+sz) - arr;
		if(arr[start] >= arr[max_index]){
			start++;
			continue;
		}
		for(i=start; i<=max_index; ++i)
			if(arr[i] == *min_element(&arr[start], &arr[max_index]))
				min_index = i;
		if(ans <= arr[max_index] - arr[min_index]){
			ans = arr[max_index] - arr[min_index];
			b = min_index;
			s = max_index;
		}
		start = max_index+1;
	}
	ofs << b+1 << ' ' << s+1 << endl;
	return 0;
}
