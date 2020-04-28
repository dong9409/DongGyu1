#include <bits/stdc++.h>

using namespace std;


class point{
	double x;
	double y;
	double z;
	friend class Vector;
public:
	point(double _x=0, double _y=0, double _z=0):x(_x), y(_y), z(_z) {}
	double distance(const point& pt)const {
		unsigned int square = (x-pt.x)*(x-pt.x) + (y-pt.y)*(y-pt.y) + (z-pt.z)*(z-pt.z);
		return pow(square,0.5);
	}
	point center(const point& pt)const{
		point p((x + pt.x)/2.0, (y + pt.y)/2.0, (z + pt.z)/2.0);
		return p;
	}
	point who_is_near(const point& A, const point& B) const{
		if(this->distance(A) >= this->distance(B))
			return B;
		else
			return A;
	}
	void print(void) const { cout << x << ',' << y << ',' << z << endl; }\
	static ceil(double num);
	~point(void){}
};

point::ceil(double num){
	if(num - int(num) > 0)
		return int(num)+1;
	else
		return int(num);
}


class Vector: point{
public:
	Vector(double _x = 0, double _y = 0, double _z = 0)
	 :point(_x, _y, _z) {}
	Vector(const point& start, const point& end) :
		point(end.x - start.x, end.y - start.y, end.z - start.z) {}
	double product(const Vector& vec) const { 
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
	ifstream ifs("station.inp");
	double ans;
	int data[9] = {0,};
	for(int i=0; i<9 && ifs>>data[i]; ++i);
	point A(data[0], data[1], data[2]);
	point B(data[3], data[4], data[5]);
	point P(data[6], data[7], data[8]);
	Vector AP(A, P);
	Vector AB(A, B);
	Vector BP(B, P);
	Vector BA = AB.reverse();
	double APAB = AP.product(AB);
	double BPBA = BP.product(BA);
	if( !(APAB>=0 && BPBA>=0) ) 
		ans = min(P.distance(A), P.distance(B));
	else {
		point now = P.who_is_near(A, B);
		point next = A.center(B);
		while(ceil(P.distance(now)) == ceil(P.distance(next)))
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
	cout << ans << endl;
	if(ans - int(ans) > 0)
		ofs << int(ans)+1 << endl;
	else
		ofs << int(ans) << endl;
	
	ofs.close();
	
	return 0;
}
