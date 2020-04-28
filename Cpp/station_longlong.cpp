#include <bits/stdc++.h>

using namespace std;

class point{
	int x;
	int y;
	int z;
	friend class Vector;
public:
	point(int _x=0, int _y=0, int _z=0)
		:x(_x), y(_y), z(_z) {}
	int distance(const point& pt)const {
		long long square = 
		(x-pt.x)*(x-pt.x) + (y-pt.y)*(y-pt.y) + (z-pt.z)*(z-pt.z);
		return pow(square,0.5);
	}
	point center(const point& pt)const{
		point p((x + pt.x)/2, (y + pt.y)/2, (z + pt.z)/2);
		return p;
	}
	point who_is_near(const point& A, const point& B) const{
		if(this->distance(A) >= this->distance(B))
			return B;
		else
			return A;
	}
	void print(void) const { cout << x << ',' << y << ',' << z << endl; }
	~point(void){}
	
};

class Vector{
	int x;
	int y;
	int z;
public:
	Vector(int _x = 0, int _y = 0, int _z = 0) : x(_x), y(_y), z(_z) {}
	Vector(const point& start, const point& end) :
		x(end.x - start.x), y(end.y - start.y), z(end.z - start.z) {}
	long long product(const Vector& vec) const { 
		return x*vec.x + y*vec.y + z*vec.z; 
	}
	Vector reverse(void) {
		Vector vc;
		vc.x = -x; vc.y = -y; vc.z = -z;
		return vc;
	}
	void print(void) const { cout << x << ',' << y << ',' << z << endl; }
	~Vector(void){}
};

int main(void)
{
	ifstream ifs("2.inp");
	if( !ifs.is_open() ) {
		cerr << "Input File Error" << endl;
		return -1;
	}
	int ans;
	int data[9] = {0,};
	for(int i=0; i<9 && ifs>>data[i]; ++i);
	
	ifs.close();
	point A(data[0], data[1], data[2]);
	point B(data[3], data[4], data[5]);
	point P(data[6], data[7], data[8]);
	
	Vector AP(A, P);
	Vector AB(A, B);
	Vector BP(B, P);
	Vector BA = AB.reverse();
	
	int APAB = AP.product(AB);
	int BPBA = BP.product(BA);
	
	if( !(APAB>=0 && BPBA>=0) ) {
		ans = min(P.distance(A), P.distance(B));
	}
	else {
		point now = P.who_is_near(A, B);
		point next = A.center(B);
		while(now.distance(next)>0.001)
		{
			if(P.distance(now) < P.distance(next)){
				ans = P.distance(now);
				next = now.center(next);
			}
			else{
				now = next.center(now);
				ans = P.distance(next);
			}
		}
	}
	
	ofstream ofs("station.out");
	if( !ofs.is_open() ) {
		cerr << "Output File Error" << endl;
		return -1;
	}
	if(ans - int(ans) > 0){
		ofs << int(ans)+1 << endl;
	}
	else{
		ofs << int(ans) << endl;
	}
	ofs.close();
	
	return 0;
}
