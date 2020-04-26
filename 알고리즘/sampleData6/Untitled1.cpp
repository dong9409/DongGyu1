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
	for(int i=0; i<len; ++i)
		cout << arr[i] << ' ';
	cout << endl;
}

int main(void){
	ifstream ifs("2.inp");
	int s, d, t, w , N, i=0, total=0;
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
	int* arr = new int[len];
	for(i=0; i<len; ++i)
		arr[i]=0;
	
	for(it=v.begin(); it!=v.end(); it++)
		arr[(*it).index-1] = (*it).value*s;
	
	//�ѹ� Ż������ ��� 
	print(arr, len); 
	print_total(arr, len);
	total = 0;
	
	//�Ϸ� Ż������ ��� 
	for(i=0; i<len; ++i){
		if(arr[i]>d)
			arr[i]=d;
	}
	print(arr, len); 
	print_total(arr, len);
	total = 0;

	
	//3�ϱ� �߰�
	for(i=0; i<len-2; ++i){
		if(arr[i]==d && arr[i+1]==d && arr[i+2]==d){
			arr[i]=t;
			arr[++i]=0;
			arr[++i]=0;
		}
	}
	print(arr, len); 
	print_total(arr, len);
	total = 0;
	
	//7�ϱ� �߰� 
	int week_total=0;
	
	for(i=0; i<len; ++i){
		if(i%7==0){
			for(int j=i; j<i+7 && j<len; ++j)
				week_total += arr[j];
			if(week_total > w){
				arr[i]=w;
				for(int j=i+1; j<i+7 && j<len; ++j)
					arr[j]=0;
				week_total=0;
			}
		}
	}
	print(arr, len); 
	print_total(arr, len);

	
	
	return 0;
}
