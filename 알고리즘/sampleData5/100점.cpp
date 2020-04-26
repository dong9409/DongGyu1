#include <bits/stdc++.h>
#include "oil.h"
 
using namespace std;

bool comp(int a, int b) {
    return (a <= b);
}
int find_left(int left, int right){
	int state = 0;
	int left_end=left;
	
	while(1){
		state = observe(left, right);
		if(state==2){
			if(right-left<=1)
				return right;
			left_end=left;
			left = (left+right)/2;
		}
		else if(state==1){
			if(right-left<=1)
				return left;
			right = left;
			left = (left_end+left)/2;
		}
	}
	return left;
}

int find_right(int left, int right){
	int state = 0;
	int right_end=right;
	
	while(1){
		state = observe(left, right);
		if(state==2){
			if(right-left<=1)
				return left;
			right_end=right;
			right = (left+right)/2;
		}
		else if(state==1){
			if(right-left<=1)
				return right;
			left = right;
			right = (right_end+left)/2;
		}
	}
	return right;
}

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
		ans.push_back(find_left(start, (start+end)/2));
		ans.push_back(find_right((start+end)/2+1, end));
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
