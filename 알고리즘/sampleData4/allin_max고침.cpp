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
};


int main(void)
{
	
	ifstream ifs("test4.inp");
	ofstream ofs("test4.out");
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
		else if(arr[i] == arr[i+1]){
			if(check == false)
				start++;
			else
				end++;
		}
		cout << start << ' ' << end << endl;
	}
	cout << endl;
	stock max = v[0];
	cout << "vector 내용 : " << endl;
	for(i=0; i<v.size(); ++i)
		cout << v[i] << endl;
	cout << "max 출력: " << endl;
	for(i=0; i<v.size(); ++i){
		if(v[i].profit > max.profit){
			max = v[i];
		}
		else if(v[i].profit == max.profit){
			max = v[i];
		}
		cout << max << endl;
	}
	cout << endl;
	cout << max << endl;
	ofs << max.start+1 << ' ' << max.end+1 <<endl;
	return 0; 
			
}
