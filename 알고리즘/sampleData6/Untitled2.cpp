#include <bits/stdc++.h>

using namespace std;

class data{
public:
	int index;
	double value;
};

void print_total(double* arr, int len){
	double total=0;
	for(int i=0; i<len; ++i)
		total += arr[i];

	cout << total << endl;
}

void print(double* arr, int len){
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
	double total=0;
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
	int len = v.back().index;
	double* arr = new double[len];
	for(i=0; i<len; ++i)
		arr[i]=0;
	
	for(it=v.begin(); it!=v.end(); it++)
		arr[(*it).index-1] = (*it).value*s;
	
	//한번 탈떄마다 계산 
	print(arr, len); 
	print_total(arr, len);
	total = 0;
	
	//하루 탈때마다 계산 
	for(i=0; i<len; ++i){
		if(arr[i]>d)
			arr[i]=d;
	}
	print(arr, len); 
	print_total(arr, len);
	total = 0;
	
	//3일권 추가
//	for(i=0; i<len-2; ++i){
//		if(arr[i]==d && arr[i+1]==d && arr[i+2]==d){
//			arr[i]=t/3;
//			arr[++i]=t/3;
//			arr[++i]=t/3;
//		}
//	}
//	print(arr, len); 
//	print_total(arr, len);
//	total = 0;
		
	//7일권 추가 
	
	double week_total=0;
	double three_days=0;
	
	for(i=0; i<len; ++i){
		if(i%7==0){
			for(int j=i; j<i+5 && j<len; ++j)
				if(arr[j]+arr[j+1]+arr[j+2]>=t){
//				if(arr[j]==d && arr[j+1]==d && arr[j+2]==d){			
					arr[j]=t/3;
					arr[++j]=t/3;
					arr[++j]=t/3;
				}
			for(int j=i; j<i+7 && j<len; ++j)
				week_total += arr[j];
				if(week_total > w){
					arr[i]=w;
					for(int j=i+1; j<i+7 && j<len; ++j)
						arr[j]=0;
				}
			week_total=0;
		}
	}
	print(arr, len); 
	print_total(arr, len);

	
	cout << len;
	return 0;
}
