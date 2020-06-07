#include <bits/stdc++.h>
using namespace std;

int k;
int result = INT_MAX;
vector<int> c;
vector<int> start;
string goal = "";
queue< vector<int> > Q;
unordered_map< string, bool > saved_state;

void readData() {
	ifstream ifs("bucket.inp");
	if (!ifs.is_open()) {
		cerr << "Error: Input File." << endl;
		return;
	}
	ifs >> k;
	int tmp;
	for (int i = 0; i < k; i++) {
		ifs >> tmp;
		c.push_back(tmp);
	}
	for (int i = 0; i < k; i++) {
		ifs >> tmp;
		start.push_back(tmp);
	}
	for (int i = 0; i < k; i++) {
		ifs >> tmp;
		goal += to_string(tmp) + " ";
	}
	ifs.close();
	return;
}

void writeData() {
	ofstream ofs("bucket.out");
	if (!ofs.is_open()) {
		cerr << "Error: Output File." << endl;
		return;
	}
	ofs << result;
	ofs.close();
	return;
}

void bucket(int out, int in, vector<int> state) {
	if ( state[out] == 0 || state[in] == c[in] ) return;

	vector<int> cur_state = state;
	if ( state[out] + state[in] >= c[in] ) {
		cur_state[out] = state[out] + state[in] - c[in];
		cur_state[in] = c[in];
	}
	else { // state[i] + state[j] < c[j]
		cur_state[out] = 0;
		cur_state[in] = state[out] + state[in];
	}
	cur_state[k] = state[k] + 1;
	
	string tmp = "";
	for (int i = 0; i < k; i++)
		tmp += to_string(cur_state[i]) + " ";
	
	if ( tmp == goal ) {
		result = cur_state[k];
		return;
	}
	
	// ���ݱ��� ����Ǿ��� state ��, ���� state�� ���� ���� �ִ��� Ȯ��. 

	auto search = saved_state.find(tmp);
	if ( search != saved_state.end() ) return;
	
	Q.push(cur_state);
	saved_state.insert(make_pair(tmp, true));

}

void bucket() {
	vector<int> start_v;
	for (int i = 0; i < k; i++)
		start_v.push_back(start[i]);
	start_v.push_back(0); // count element;
	
	Q.push(start_v);
	
	while( !Q.empty() && result == INT_MAX ) {
		vector<int> state = Q.front();
		Q.pop();
		
		for (int i = 0; i < k; i++) {
			for (int j = 0; j < k; j++)
				if ( i != j ) bucket(i, j, state);
		}
	}
	
	if ( result == INT_MAX ) result = 0;
}


int main(void) {
	readData();
	bucket();
	writeData();
	return 0;
}