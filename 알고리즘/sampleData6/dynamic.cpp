#include <bits/stdc++.h>

using namespace std;

class data{
public:
	int index;
	int value;
};

void print_total(int* arr, int len){
	int total=0;
	for(int i=0; i<len; ++i)
		total += arr[i];

	cout << total << endl;
}

void print(int* arr, int len){
	for(int i=0; i<len; ++i){
		cout << arr[i] << ' ';
	}
	cout << endl;
}

void week_print(int* arr, int len){
	for(int i=0; i<len; ++i){
		if(i%7==0)
			cout << endl;
		cout << arr[i] << ' ';
	}
	cout << endl;
}


int main(void){
	ifstream ifs("3.inp");
	int s, d, t, w , N, i=0;
	int total=0;
	data temp;
	ifs >> s >> d >> t >> w >> N;
	
	vector<data> v;
	vector<data>::iterator it;
	
	while(i<N){
		ifs >> temp.index;
		ifs >> temp.value;
		v.push_back(temp);
		i++;
	}
	int len = v.back().index+1;
	int* arr = new int[len];
	int* ans = new int[len];
	
	for(i=0; i<len; ++i){
		arr[i]=0;
		ans[i]=0;
	}
	
	for(it=v.begin(); it!=v.end(); it++)
		arr[(*it).index] = (*it).value;
	
	ans[1] = min(arr[1]*s, d);
	int temp1 = min(ans[1] + arr[2]*s, ans[1]+d);
	ans[2] = min(temp1, t);
	
	print(arr+1, len-1);
	cout << endl;
	
	for(i=3; i<len; ++i){
		vector<int> money;
		money.push_back(ans[i-1] + arr[i]*s);
		money.push_back(ans[i-1] + d);
		money.push_back(ans[i-3] + t);
		if(i%7==0){
			money.push_back(ans[i-7] + w);
			sort(money.begin(), money.end());
			ans[i] = money[0];			
		}
		else if(i==len-1){
			money.push_back(ans[i-i%7] + w);
			sort(money.begin(), money.end());
			ans[i] = money.front();			
		}
		sort(money.begin(), money.end());
		ans[i] = money.front();			
	}
	cout << ans[len-1] << endl;
	return 0;
}
