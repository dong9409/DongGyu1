#include <bits/stdc++.h> //20�� 
#include "oil.h"
 
using namespace std;

void binary_search(int start, int end, vector<int>& ans){
	if(observe(start, end) == 2){
		binary_search(start, (start+end)/2, ans);
		binary_search((start+end)/2+1, end, ans);
	}
	else if(observe(start, end) == 1){
		ans.push_back(start);
		ans.push_back(end);
		return ;
	}
}

int main(void){
	initial();
	int N = oil_size();
	vector<int> ans;
	binary_search(0, N-1, ans);
	
	oil_report(ans.front(), ans.back());
	return 0;
}
