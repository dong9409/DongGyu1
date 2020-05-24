#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <math.h>

using namespace std;

int min_energy = 200000;
bool check[20];
int N;

typedef struct{
	int h;
	int w;
	int x;
	int y;
} Set;


int get_distance(Set& a, Set& b){
	return abs(a.x-b.x) + abs(a.y-b.y);
}

int get_energy(Set& a, Set& b, int w){
	return w * get_distance(a, b);
}


void back_tracking(vector<Set>& matrix, vector<Set>& ans, 
					int c, int distance, int total_weight, int E){
	if(c==N){
		E = E + get_energy(ans[c-1], ans[0], total_weight);
		if(E <= min_energy){
			min_energy = E;
		}
		return ;
	}
	
	for(int i=1; i<N; ++i){
		if(E < min_energy && check[matrix[i].h] == false){
			check[matrix[i].h]=true;
			ans.push_back(matrix[i]);
			int temp1 = E;
			int temp2 = distance;;
			distance = get_distance(ans[c-1], ans[c]);
			E = E + get_energy(ans[c-1], ans[c], total_weight);
			total_weight = total_weight - ans[c].w;
			back_tracking(matrix, ans, c+1, distance, total_weight, E);
			ans.erase(ans.end()-1);
			E = temp1;
			distance = temp2;
			total_weight = total_weight + ans[c].w;
			check[matrix[i].h]=false;
		}
	}
}

int main(void){	
	int h, w, x, y;
	int total_weight=1;
	vector<Set> matrix;
	vector<Set> ans;
	ifstream in("drone.inp");
	
	in >> N;
	int i=0;
	
	while(i<N){
		in >> h >> w >> x >> y;
		total_weight += w;
		Set temp = {h, w, x, y};
		if(h == 1)
			matrix.insert(matrix.begin(), temp);
		else if(h != 1)
			matrix.push_back(temp);
		++i;
		
	}
	
	ans.push_back( *(matrix.begin()) );
	check[1] = true;
	back_tracking(matrix, ans, 1, 0, total_weight, 0);
	ofstream out("drone.out");
	out << min_energy;
	
	out.close();
	in.close();
	return 0;
}
