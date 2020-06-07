#include <bits/stdc++.h>

using namespace std;

ifstream ifs("10.inp");
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


void record(vector<bucket> vv){
	vector<int> temp;
	for(auto it: vv)
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
bool check_visit(vector<bucket> b){
	for(int i=0; i<check.size(); i++){
		for(int j=0; j<check[i].size(); ++j){
			if(b[j].water != check[i][j])
				break;
			if(j == check[i].size()-1)
				return true;
		}
	}
	return false;
}
bool promising(vector<bucket> v){
	for(int i=0; i<N; ++i){
		if(v[i].water != goal[i])
			return false;
	}
	return true;
}
void print(vector<bucket> v){
	for(auto it : v)
		ofs << it;
}
void print_check(){
	for(int i=0; i<check.size(); i++){
		for(int j=0; j<check[i].size(); ++j){
			ofs << check[i][j] << ' ';
		}
		ofs << endl;
	}
}

int BFS(){
	int level=0;
	queue < pair<vector<bucket>, int> > que;
	que.push(make_pair(v, level));

	
	while(!que.empty()){
//		print_check();
//		ofs << endl;
		vector<bucket> temp = que.front().first;
		level = que.front().second;
//		print(temp);
//		ofs << "C: " << que.front().second << endl << endl;
		que.pop();
		
		if(check_visit(temp) == true)
			continue;
		if(promising(temp) == true){
			return level;
		}
		record(temp);
		
		for(int i=0; i<N; ++i){
			for(int j=0; j<N; ++j){
				if(i!=j  && temp[i].water!=0 && temp[j].remain()!=0){
					bucket temp1 = temp[i];
					bucket temp2 = temp[j];
					temp[i].process(temp[j]);
					que.push(make_pair(temp, level+1));
					
					temp[i] = temp1;
					temp[j] = temp2;
				}
			}
		}
	}
	return 0;
}
	


int main(void){
	init();
	cout << BFS();
	
	return 0;
}
