#include <bits/stdc++.h>

using namespace std;

ifstream ifs("3.inp");
ofstream ofs("drone.out");

class location{
public:
	int id;
	int w;
	int x;
	int y;
public:
	location(int _id=0, int _w=0, int _x=0, int _y=0): id(_id), w(_w), x(_x), y(_y) {}
	friend ostream& operator<<(ostream& os, const location& lc){
		os << lc.id << ' ' << lc.w << ' ' << lc.x << ' ' << lc.y << endl;
		return os;
	}
	int distance(const location& lc)const{
		return abs(x-lc.x) + abs(y-lc.y);
	}
	
};

int min_v = 200000;
vector<location> v;
bool chk_visit[20];
int c=0;

void drone(vector<location>& order, int N, int z, int dist, int total_w, int energy){

	if(z==N){
		energy = energy + order[z-1].distance(v[0]);
		if(energy <= min_v){
			min_v = energy;
		}
		return ;
	}
	for(int i=1; i<N; ++i){
		int h = v[i].id;
		if(energy < min_v && chk_visit[h] == false){
			chk_visit[h]=true;
			order.push_back(v[i]);
			int energy_temp = energy;
			int dist_temp = dist;
			int w_temp = total_w;
			
			dist = order[z-1].distance(order[z]);
			energy = energy + total_w * dist;
			total_w = total_w - order[z].w;
			
			drone(order, N, z+1, dist, total_w, energy);
			
			order.pop_back();
			energy = energy_temp;
			dist = dist_temp;
			total_w = w_temp;
			chk_visit[h]=false;
		}
	}
}

int main(void){	
	int N, id, w, x, y;
	vector<location> order;
	
	ifs >> N;
	int total_w=1;
	
	for(int i=0; i<N; ++i){
		ifs >> id >> w >> x >> y;
		location temp = location(id, w, x, y);
		total_w += w;
		if(id==1)
			v.insert(v.begin(), temp);
		else
			v.push_back(temp);
	}
	order.push_back(v[0]);
	chk_visit[1] = true;
	drone(order, N, 1, 0, total_w, 0);
	cout << min_v;
	return 0;
}
