#include <bits/stdc++.h>

using namespace std;

ifstream ifs("1.inp");
ofstream ofs("t.out");

class bucket{
public:
	int limit;
	int water;
public:
	bucket(int _limit, int _water):
		limit(_limit), water(_water) {}
	int remain(void) { return limit-water; } 
	
	void process(bucket& b){
	//b의 남은 용량이 this의 water보다 클 때 
		if(b.remain() >= this->water){
			b.water += this->water;
			this->water=0;
		}
		
		else if(b.remain() < this->water){
			this->water -= b.remain();
			b.water = b.limit;
		}
		
	}
	friend ostream& operator<<(ostream& os, const bucket& b){
		os << b.limit << ' ' << b.water << endl ;
		return os;
	}
	
};

int N;
int goal[6];

vector<bucket> v;
vector< vector<int> > check;

int c=0;

void record(void){
	vector<int> temp;
	for(auto it: v)
		temp.push_back(it.water);
	check.push_back(temp);
}

void init(void){
	ifs >> N;
	int** arr = new int*[3];
	
	for(int i=0; i<3; ++i)
		arr[i] = new int[N];
	
	for(int i=0; i<3; ++i)
		for(int j=0; j<N; ++j)
			ifs >> arr[i][j];
	
	for(int j=0; j<N; ++j)
		v.push_back(bucket(arr[0][j], arr[1][j]));
	
	for(int j=0; j<N; ++j){
		goal[j] = arr[2][j];
	}
	delete[] arr;
}

bool check_visit(void){
	for(int i=0; i<check.size(); i++){
		for(int j=0; j<check[i].size(); ++j){
//			cout << j << "water " << v[j].water << ' ' << check[i][j] << endl;
			if(v[j].water != check[i][j])
				break;
			if(j == check[i].size()-1)
				return true;
		}
	}
	return false;
}

bool promising(void){
	for(int i=0; i<N; ++i){
		if(v[i].water != goal[i])
			return false;
	}
	return true;
}
vector<int> ans;
void back_tracking(int now){
	if(promising() == true){
		ans.push_back(c);
		return ;
	}
	
	if(check_visit == false){
		for(int i=0; i<v.size(); ++i){
			if(now != i){
				bucket temp = v[now];
				vector< <vector<int> > temp2 = check;
				++c;
				v[now].process(v[i]);
				record();
				
				back_tracking(i);
				
				v[now] = temp;
				check = temp2;
				--c;
			}
		}
	}
	
}

int main(void){
	init();
	back_tracking(0);

	return 0;
}
