#include <bits/stdc++.h>

using namespace std;

ifstream ifs("1.inp");
ofstream ofs("t.out");

class bucket{
public:
	int limit;
	int water;
	int goal;
public:
	bucket(int _limit, int _water, int _goal):
		limit(_limit), water(_water), goal(_goal) {}
	int remain(void) { return limit-water; } 
	//b의 남은 용량이 클 때this의 water보다 클 때 
	void fun1(bucket& b){
		b.water += water;
		water=0;
	}
	//b의 남은 용량이 this의 water보다 작을 때
	void fun2(bucket& b){
		water -= b.remain();
		b.water = b.limit;
	}
	friend ostream& operator<<(ostream& os, const bucket& b){
		os << b.limit << ' ' << b.water << ' ' << b.goal << endl;
		return os;
	}
};

int N;
vector<bucket> v;

void init(void){
	int N;
	ifs >> N;
	int** arr = new int*[3];
	
	for(int i=0; i<3; ++i)
		arr[i] = new int[N];
	
	for(int i=0; i<3; ++i)
		for(int j=0; j<N; ++j)
			ifs >> arr[i][j];
	
	for(int j=0; j<N; ++j)
			v.push_back(bucket(arr[0][j], arr[1][j], arr[2][j]));
}
int main(void){
	init();
	for(auto it: v)
		cout << it;
	return 0;
}
