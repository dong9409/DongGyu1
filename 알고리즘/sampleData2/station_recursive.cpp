#include <bits/stdc++.h>

using namespace std;

class point{
	double x;
	double y;
	double z;
	static int num;
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
	void print(void) const { cout << x << ',' << y << ',' << z << endl; }
	point binary_search(point left, point right) const {
		if( ceil(this->distance(left)) == ceil(this->distance(right))){
			return left.center(right);
		}
		else if( ceil(this->distance(left)) > ceil(this->distance(right)) ) {
			left = left.center(right);
			return binary_search(left, right);
		}
		else{
			right = right.center(left);
			return binary_search(left, right);
		}
	}
	~point(void){}
};

int main(void)
{
	ifstream ifs("1.inp");
	double data[9] = {0,};
	for(int i=0; i<9 && ifs>>data[i]; ++i);
	point p1, p2;
	point A(data[0], data[1], data[2]);
	point B(data[3], data[4], data[5]);
	point P(data[6], data[7], data[8]);

	p1 = P.binary_search(A, B);
	cout << p1.distance(P) << endl;
	
	
	return 0;
}
