#include <bits/stdc++.h>

using namespace std;

class data{
public:
	int index;
	double value;
};

int get_total(double* arr, int len){
	double total=0;
	for(int i=0; i<len; ++i)
		total += arr[i];

	return total;
}

int main(void){
	ifstream ifs("ticket.inp");
	ofstream ofs("ticket.out");
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

	
	//하루 탈때마다 계산 
	for(i=0; i<len; ++i){
		if(arr[i]>d)
			arr[i]=d;
	}

	double week_total=0;
	double three_days=0;
	
	for(i=0; i<len; ++i){
		if(i%7==0){
			for(int j=i; j<i+5 && j<len; ++j)
				if(arr[j]+arr[j+1]+arr[j+2]>=t){		
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
	ofs << get_total(arr, len);
	delete[] arr;
	return 0;
}
