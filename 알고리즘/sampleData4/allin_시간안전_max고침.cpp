#include <bits/stdc++.h>

using namespace std;

class stock{
public:
	int start;
	int end;
	short profit;
public:
	stock(int _start, int _end, short* arr) : start(_start), end(_end)
	{ profit = arr[_end]- arr[_start]; }
};


int main(void)
{
	
	ifstream ifs("3.inp");
	ofstream ofs("3t.out");
	int i = 0;
	int sz;
	short* arr;
	ifs >> sz;
	arr = new short[sz];
	vector<stock> v;
	
	while(ifs>>arr[i])
		i++;
	int start=0;
	int end=0;
	bool check = false;
	
	for(i=0; i<sz; ++i){
		if(arr[i] < arr[i+1]){
			end = i+1;
			check = true;
			if(i==sz-2){
				v.push_back(stock(start, end, arr));
				break;
			}
		}
		else if(arr[i] == arr[i+1])
			continue;
		else if(arr[i] > arr[i+1]){
			if(check == true){
				if(i == sz-2){
					v.push_back(stock(start, end, arr));
					break;
				}
				v.push_back(stock(start, end, arr));
				start = end+1;
				check = false;
			}
			else if(check == false)
				start++;
		}
	}
	stock max = v[0];
	for(i=0; i<v.size(); ++i)
		if(v[i].profit >= max.profit)
			max = v[i];
			
	delete []arr;
	ofs << max.start+1 << ' ' << max.end+1;
	ifs.close();
	ofs.close();
	return 0; 
			
}
