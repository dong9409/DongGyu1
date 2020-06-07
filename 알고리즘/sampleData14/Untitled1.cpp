#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

ifstream ifs("1.inp");
ofstream ofs("t.out");

int** graph;
int N;

void print(void){
	for(int i=0; i<N; ++i){
		for(int j=0; j<N; ++j){
			cout << graph[i][j] << ' ';			 
		}
		cout << endl;
	}
}

void init(void){
	int temp=-1;
	ifs >> N;
	graph = new int*[N];
	for(int i=0; i<N; ++i)
		graph[i] = new int[N];
	
	for(int i=0; i<N; ++i){
		for(int j=0; j<N; ++j){
			graph[i][j]=0;
		}
	}
	for(int i=0; i<N; ++i){
		vector<int> v;
		while(temp!=0){
			ifs >> temp;
			v.push_back(temp);
		}
		for(auto it:v)
			cout << it << ' ';
		cout << endl;
	}
	print();
}
int main(void){
	init();
	print();
	return 0;
}
