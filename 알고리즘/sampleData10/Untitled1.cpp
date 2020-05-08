#include <bits/stdc++.h>

using namespace std;

bool chk_row[9][9];
bool chk_col[9][9];
int c=0;

ifstream ifs("test.inp");
ofstream ofs("1t.out");

bool possible_data(int** arr, int N){
	for(int x=0; x<N; ++x){
		for(int i=0; i<N-1; ++i){
			for(int j=i+1; j<N; ++j){
				if(arr[x][i] == arr[x][j])
					return false;
			}
		}
	}
	
	for(int y=0; y<N; ++y){
		for(int i=0; i<N-1; ++i){
			for(int j=i+1; j<N; ++j){
				if(arr[i][y] == arr[i][y])
					return false;
			}
		}
	}
	return true;
	
}
void print(int** arr, int N){
	for(int i=0; i<N; ++i){
		for(int j=0; j<N; ++j){
			cout << arr[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void ofs_print(int** arr, int N){
	for(int i=0; i<N; ++i){
		for(int j=0; j<N; ++j){
			ofs << arr[i][j] << ' ';
		}
		ofs << endl;
	}
	ofs << endl;
}
void pizza(int** arr, int N, int z){
	//ºóÄ­ Ã£±â 
	ofs << z << endl;
	ofs_print(arr, N);
	
	if(z == N*N){
		c++;
		return;
	}
	
	int x = z/N, y = z%N;
	
	if(arr[x][y]!=0)
		pizza(arr, N, z+1);
	else{
		for(int i=1; i<=N; ++i){
			if(!chk_row[x][i] && !chk_col[y][i])
			{
				chk_row[x][i]=true;
				chk_col[y][i]=true;
				arr[x][y] = i;
				pizza(arr, N, z+1);
				arr[x][y]=0;
				chk_row[x][i]=false;
				chk_col[y][i]=false;
			}
		}
	}
}

void init(int** arr, int N){
	for(int i=0; i<N; ++i){
		for(int j=0; j<N; ++j){
			int num = arr[i][j];
			
			if(num !=0 ){
				chk_row[i][num] = true;
				chk_col[j][num] = true;
			}
		}
	}
}

int main(void){
	
	int N;
	ifs >> N;
	
	int** arr = new int*[N];
	for(int i=0; i<N; ++i)
		arr[i] = new int[N];
	
	for(int i=0; i<N; ++i)
		for(int j=0; j<N; ++j)
			ifs >> arr[i][j];
	
	init(arr, N);
	if(possible_data(arr, N) == true)
		pizza(arr, N, 0);
	cout << c;
	return 0;
}
