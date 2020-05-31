#include<bits/stdc++.h>

using namespace std;

ifstream ifs("diet.inp");
ofstream ofs("diet.out");

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
bool check[100];
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
		cout << it;
	cout << endl;
}

void print_ofs(vector<food> v){
	for(auto it: v)
		ofs << it.i << ' ';
}

int get_price(vector<food>& order){
	int sum=0;
	for(auto it: order)
		sum += it.price;
	return sum;
}

int get_material(vector<food>& order){
	int sum=0;
	for(auto it: order){
		sum += it.a + it.b + it.c + it.d;
	}
	return sum;
}

bool condition(vector<food>& order){
	int aa=0, bb=0, cc=0, dd=0;
	for(auto it: order){
		aa += it.a;
		bb += it.b;
		cc += it.c;
		dd += it.d;
	}
	if(aa>=sum_condition[0] && bb>=sum_condition[1] 
		&& cc>=sum_condition[2] && dd>=sum_condition[3])
			return true;
			
	else
		return false;
}

vector<food> comp(vector<food>& a, vector<food>& b){
	int n;
	vector<food> temp;
	if(a.size() >= b.size()){
		n = b.size();
		temp = a;
	}
	else{
		n = a.size();
		temp = b;
	}
		
	for(int i=0; i<n; ++i){
		if(a[i].i < b[i].i)
			return a;
		else if(a[i].i > b[i].i)
			return b;
	}
	return temp;
}


void Diet(vector<food>& order){
	int price_total = get_price(order);
	int material_total = get_material(order);
	bool promising = condition(order);
	
	if(promising == true){
		if(min_price > price_total){
			min_price = price_total;
			max_material = material_total;
			ans = order;
			return;
		}
		else if(min_price == price_total){
			if(max_material < material_total){
				ans = order;
				max_material = material_total;
				return ;
			}
			else if(max_material == material_total){
				ans = comp(ans, order);
				return ;
			}
		}
	}
	
	for(int i=0; i<N; ++i){
		if(check[i] == false && promising==false){
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
}

int main(void){
	
	init();
	vector<food> order;
	Diet(order);
	print_ofs(ans);
	
	return 0;
}
