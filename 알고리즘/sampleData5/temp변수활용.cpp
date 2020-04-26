#include <bits/stdc++.h>
#include "oil-openVer.h"
 
using namespace std;

bool comp(int a, int b) {
    return (a <= b);
}

int call = 0;

void binary_search(int start, int end, vector<int>& ans){
	if(observe(start, end) == 2){
		cout << "call:" << ++call << endl;
		cout << "start:" << start << ' ' << "end:" << end << endl;
		binary_search(start, (start+end)/2, ans);
		binary_search((start+end)/2+1, end, ans);
	} 
	else if(observe(start, end) == 1) {
		cout << "call:" << ++call << endl;
		cout << "start:" << start << ' ' << "end:" << end << endl;
		ans.push_back(start);
		ans.push_back(end);
	}
	else{
		cout << "call:" << ++call << endl;
		cout << "start:" << start << ' ' << "end:" << end << endl;
	}
	
}

int main(void){
	initial();
	int N = oil_size();
	vector<int> ans;
	binary_search(0, N-1, ans);
	sort(ans.begin(), ans.end(), comp);
	vector<int>::iterator it;
	for(it=ans.begin(); it!=ans.end(); it++)
		cout << *it << ' ';
	cout << endl; 
	oil_report(ans.front(), ans.back());
	return 0;
}
