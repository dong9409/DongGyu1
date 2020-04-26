#include <bits/stdc++.h>
#include "oil-openVer.h"
 
using namespace std;

int find_left(int left, int right){
	int i=0;
	int state = 0;
	int left_end=left;
	
	while(1){
		cout << "left=" << left << ' ' << "right=" << right << ' '<<
		"left_end=" << left_end <<endl;
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
		++i;
	}
	return left;
}

int find_right(int left, int right){
	int i=0;
	int state = 0;
	int right_end=right;
	
	while(i<10){
		cout << "left=" << left << ' ' << "right=" << right << ' '<<
		"right_end=" << right_end <<endl;
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
		++i;
	}
	return right;
}
int main(void){
	initial();
	int N = oil_size();
//	cout << find_left(0, (N-1)/2-1);
	cout << find_right((N-1)/2, N-1);
	return 0;
}
