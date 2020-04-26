#include <bits/stdc++.h>
#include "oil-openVer.h"
 
using namespace std;

bool comp(int a, int b) {
    return (a <= b);
}

int num = 0;

void binary_search(int start, int end, vector<int>& ans){
	int left_observe = observe(start, (start+end)/2 );
	int right_observe = observe((start+end)/2+1, end);
	
	if(left_observe == 1 && right_observe == 1){
		ans.push_back(start);
		ans.push_back(end);
	}
	
	else if(left_observe == 0 && right_observe == 1){
		ans.push_back((start+end)/2+1);
		ans.push_back(end);
	}
	
	else if(left_observe == 1 && right_observe == 0){
		ans.push_back(start);
		ans.push_back((start+end)/2);
	}
	
	else if(left_observe == 0 && right_observe == 2)
		binary_search((start+end)/2+1, end, ans);
		
	else if(left_observe == 2 && right_observe == 0)
		binary_search(start, (start+end)/2, ans);
		
	else if(left_observe == 1 && right_observe == 2){
		ans.push_back(start);
		ans.push_back((start+end)/2);
		binary_search((start+end)/2+1, end, ans);
	}
	else if(left_observe == 2 && right_observe == 1){
		ans.push_back((start+end)/2+1);
		ans.push_back(end);	
		binary_search(start, (start+end)/2, ans);
	}
	else if(left_observe == 2 && right_observe == 2){
		binary_search(start, (start+end)/2, ans);
		binary_search((start+end)/2+1, end, ans);
	}
}

int main(void){
	initial();
	int N = oil_size();
	vector<int> ans;
	binary_search(0, N-1, ans);
	sort(ans.begin(), ans.end(), comp);
	oil_report(ans.front(), ans.back());
	return 0;
}
