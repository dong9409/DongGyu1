#include <bits/stdc++.h>

using namespace std;

ifstream ifs("bucket.inp");
ofstream ofs("bucket.out");

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
int minv=200000;

vector<bucket> v;
vector< vector<int> > check;


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

void back_tracking(int now, int c){

		
	if(promising() == true){
		if(c <= minv){
			minv = c;
		}
	}
	if(check_visit() == true)
		return;

	if(promising() == false)
		record();
		
	for(int i=0; i<v.size(); ++i){
		if(i != now && c<minv){
			bucket temp1 = v[now];
			bucket temp2 = v[i];
			v[now].process(v[i]);
			
			back_tracking(i, c+1);
			
			v[now] = temp1;
			v[i] = temp2;
			
		}			
	}
}
	


int main(void){
	init();
	back_tracking(0,0);
	if(minv != 200000)
		ofs << minv << endl;
	else
		ofs << 0 << endl;
	return 0;
}
