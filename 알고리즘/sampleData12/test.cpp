#include<bits/stdc++.h>

using namespace std;

ifstream ifs("1.inp");
ofstream ofs("t.out");

class food{
public:
	int i, a, b, c, d, price;
public:
	food(int _i, int _a, int _b, int _c, int _d, int _price):
		i(_i), a(_a), b(_b), c(_c), d(_d), price(_price) {}
		
	friend ostream& operator<<(ostream& os, const food& f){
		os << f.i << ' ' << f.a << ' ' << f.b << ' ' << f.c << ' ' << f.d << ' ' << f.price << endl;
		return os;
	}
};

int sum_condition[4];
bool check[30];
vector<food> food_list;
vector<food> ans;

int min_price=200000;
int max_material=0;
int N;

void init(void){
	ifs >> N;
	ifs >> sum_condition[0] >> sum_condition[1] >> sum_condition[2] >> sum_condition[3];
	int a, b, c, d, price;
	for(int i=1; i<=N; ++i){
		ifs >> a >> b >> c >> d >> price;
		food_list.push_back(food(i, a, b, c, d, price));
	}
}

void print(vector<food> v){
	for(auto it: v)
		cout << it.i << ' ';
	cout << endl;
}

int c=0;
void Diet(vector<food>& order){
	++c;
	print(order);
	for(int i=0; i<N; ++i){
		if(check[i] == false){
			for(int j=0; j<=i; ++j)
				check[j] = true;
			order.push_back(food_list[i]);
			
			Diet(order);
			
			order.pop_back();
			for(int j=0; j<=i; ++j)
				check[j] = false;
		}
	}
}

int main(void){
	
	init();
	vector<food> order;
	Diet(order);
	return 0;
}





