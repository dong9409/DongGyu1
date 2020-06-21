#include<bits/stdc++.h>

using namespace std;

struct cord{
	int order, x, y;
};

bool myfun(cord B, cord C){
	cord A={0,0};
	int sa = A.x*B.y + B.x*C.y + C.x*A.y - (B.x*A.y + C.x*B.y + A.x*C.y);
	if(sa > 0)
		return true;
	else if(sa == 0){
		if(B.x*B.x < C.x*C.x)
			return true;
		else
			return false;
	}
	else
		return false;
}
int main(void){
	ifstream ifs("1.inp");
	vector<cord> q1;
	vector<cord> q2;
	vector<cord> q3;
	vector<cord> q4;
	int num;
	ifs >> num;
	int order=1;
	for(int i=0; i<num; ++i){
		int x, y;
		ifs >> x >> y;
		if(x>0 && y>=0)	
			q1.push_back({order,x,y});
		else if(x<=0 && y>0)
			q2.push_back({order,x,y});
		else if(x<0 && y<=0)
			q3.push_back({order,x,y});
		else if(x>=0 && y<0)
			q4.push_back({order,x,y});
		order++;
	}
	
	for(auto it:q1)
		cout << it.x << ' ' << it.y << endl;
	for(auto it:q2)
		cout << it.x << ' ' << it.y << endl;
	for(auto it:q3)
		cout << it.x << ' ' << it.y << endl;
	for(auto it:q4)
		cout << it.x << ' ' << it.y << endl;
	cout << endl;
	sort(q1.begin(), q1.end(), myfun);
	sort(q2.begin(), q2.end(), myfun);
	sort(q3.begin(), q3.end(), myfun);
	sort(q4.begin(), q4.end(), myfun);
	
	
	for(auto it:q1)
		cout << it.order << endl;
	for(auto it:q2)
		cout << it.order << endl;
	for(auto it:q3)
		cout << it.order << endl;
	for(auto it:q4)
		cout << it.order << endl;
		
	return 0;
}
