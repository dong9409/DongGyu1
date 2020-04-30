#include <bits/stdc++.h>

//https://makefortune2.tistory.com/110
//https://mantdu.tistory.com/746

using namespace std;

class info{
public:
	int i0, i1, i2, i3, i4;
public:
	info(int _i0, int _i1, int _i2, int _i3, int _i4, int* arr):
		i0((10994-_i0)/arr[4]), i1((_i0-_i1)/arr[3]), i2((_i1-_i2)/arr[2])
		, i3((_i2-_i3)/arr[1]), i4((_i3-_i4)/arr[0]){}
	void print(void)const{
		cout << i0 << ' ' << i1 << ' ' <<
		i2 << ' ' <<
		i3 << ' ' <<
		i4 <<endl;
	}
};
int main(void){
	ifstream ifs("3.inp");
	ofstream ofs("3t.out");
	int L;
	int n;
	ifs >> L >> n;
	int* arr = new int[n];
	int* x = new int[n];
	
	for(int i=0; i<n; ++i){
		ifs >> arr[i];
		x[i]=-1;
	}

	int i0, i1, i2, i3, i4;
	int count=0;
	vector<info> v;
	vector<info>::iterator it;
	for(i0 = L; i0>=0; i0=i0-arr[n-1]){
		for(i1 = i0; i1>=0; i1=i1-arr[n-2]){
			for(i2 = i1; i2>=0; i2=i2-arr[n-3]){
				for(i3 = i2; i3>=0; i3=i3-arr[n-4]){
					for(i4 = i3; i4>=0; i4=i4-arr[n-5]){
						if(i4 == 0){
							printf("%d %d %d %d %d\n", i0, i1, i2, i3, i4);
							v.push_back(info(i0,i1,i2,i3,i4,arr));
							count++;
						}
					}
				}
			}
		}
	}
	for(it=v.begin(); it!=v.end(); ++it)
		(*it).print();
	cout << count;
	return 0;
}
