#include <bits/stdc++.h>

using namespace std;

class stock{
public:
	int start;
	int end;
	short profit;
public:
	stock(int _start, int _end, short* arr) : start(_start), end(_end)
	{profit = arr[_end]- arr[_start];}
	friend ostream& operator <<(ostream& os, const stock& st){
		cout << '(' << st.start+1 << ',' << st.end+1 << ')' << "  "
			<< "profit =" << st.profit;
		return os;
	}
	const stock& greater_b(const stock& st) const {
		if(start > st.start)
			return *this;
		else if(start < st.start)
			return st;
	}
};


int main(void)
{
	
	ifstream ifs("3t.inp");
	ofstream ofs("3tt.out");
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
		cout << start << ' ' << end << endl;
	}
	cout << endl;
	stock max = v[0];
	for(i=0; i<v.size(); ++i)
	 cout << v[i] << endl;
	for(i=0; i<v.size(); ++i){
		if(v[i].profit > max.profit){
			max = v[i];
		}
		else if(v[i].profit == v[i+1].profit){
			max = v[i].greater_b(v[i+1]);
		}
	}
	cout << max << endl;
	ofs << max.start+1 << ' ' << max.end+1 <<endl;
	return 0; 
			
}
