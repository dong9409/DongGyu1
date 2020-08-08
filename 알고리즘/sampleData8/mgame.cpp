#include <bits/stdc++.h>

using namespace std;

class line{
public:
	int** max_v;
	int** min_v;
	char* arr;
	int len;
	int m;
	
public:
	line(char* _arr, int _len):m(_len/2+1), len(_len){
		arr = new char[len];
		max_v = new int*[m];
		min_v = new int*[m];
		
		for(int i=0; i<len; ++i)
			arr[i] = _arr[i];
		for(int i=0; i<m; ++i)
			max_v[i] = new int[m];
		for(int i=0; i<m; ++i)
			for(int j=0; j<m; ++j)
				max_v[i][j]=-100000;
		for(int i=0; i<m; ++i)
			min_v[i] = new int[m];
		for(int i=0; i<m; ++i)
			for(int j=0; j<m; ++j)
				min_v[i][j]=100000;
	}
	
	void init(void){
		for(int i=0; i<m; ++i)
			for(int j=0; j<m; ++j)
				if(i==j){
					max_v[i][i]=arr[i*2]-'0';
					min_v[i][i]=arr[i*2]-'0';
				}
	}
	
	int process(void){
		for(int l=1; l<m; ++l)
			for(int i=0; i+l<m; ++i){
				int j = i+l;
				
				for(int k=i; k<j; ++k){
					if(arr[k*2+1]=='+'){
						max_v[i][j] = max(max_v[i][j], max_v[i][k] + max_v[k+1][j]);
						min_v[i][j] = min(min_v[i][j], min_v[i][k] + min_v[k+1][j]);
					}
					else if(arr[k*2+1]=='-'){
						max_v[i][j] = max(max_v[i][j], max_v[i][k] - min_v[k+1][j]);
						min_v[i][j] = min(min_v[i][j], min_v[i][k] - max_v[k+1][j]);
					}
					else if(arr[k*2+1]=='*'){
						int temp1 = min(max_v[i][k] * max_v[k+1][j], min_v[i][k] * min_v[k+1][j]);
						int temp2 = min(temp1, max_v[i][k] * min_v[k+1][j]);
						max_v[i][j] = max(max_v[i][j], max(max_v[i][k] * max_v[k+1][j], min_v[i][k] * min_v[k+1][j]));
						min_v[i][j] = min(min_v[i][j], temp2);
					}
				}
			}
		return max_v[0][m-1];
	}
	
	int ans(void)const {
		return max_v[0][m-1];
	}
			
	void print_arr(void)const{
		for(int i=0; i<len; ++i)
			cout << arr[i] << ' ';
	}
	~line(void){
		delete[] arr;
		delete[] max_v;
		delete[] min_v;
	}
};


int main(void){
	ifstream ifs("mgame.inp");
	ofstream ofs("mgame.out");
	
	char arr[100] = {0,};
	char temp;
	int len=0;
	
	while(ifs>>temp){
		arr[len] = temp;
		len++;
	}
	
	line game(arr, len);
	game.init();
	int ans = game.process();
	ofs << ans << endl;
	ifs.close();
	ofs.close();
	return 0;
}
