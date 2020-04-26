#include <bits/stdc++.h>

using namespace std;

class point{
	double x;
	double y;
	double z;
	static int num;
public:
	point(double _x=0, double _y=0, double _z=0):x(_x), y(_y), z(_z) {}
	point(double* ptr){
		double* index = ptr + num;
		x = *(index); y = *(index+1); z = *(index+2);
		num += 3;
	}
	double distance(const point& pt)const {
		double square = (x-pt.x)*(x-pt.x) + (y-pt.y)*(y-pt.y) + (z-pt.z)*(z-pt.z);
		return pow(square,0.5);
	}
	point center(const point& pt)const{
		point p((x + pt.x)/2.0, (y + pt.y)/2.0, (z + pt.z)/2.0);
		return p;
	}
	void print(void) const { cout << x << ", " << y << ", " << z << endl; }
	point binary_search(point left, point right) const { //&붙이면 큰일남 
		if( this->distance(left) == this->distance(right) ){
//			cout << ceil(this->distance(left.center(right))) << endl;
			return left.center(right);
		}
		else if( this->distance(left) > this->distance(right) ) {
			left = left.center(right); // &쓰면 여기서 left 값 자체가 바뀜 
			return binary_search(left, right);
		}
		else{
			right = right.center(left);
			return binary_search(left, right);
		}
	}
	~point(void){}
};

int point::num=0;

int main(void)
{
	ifstream ifs("1.inp");
	ofstream ofs("station.out");
	
	double data[12] = {0,};
	for(int i=0; i<12 && ifs>>data[i]; ++i);
	ifs.close();
	
	point A(data); point B(data);
	point C(data); point D(data);
	point p, q;	
	
	int index = 0; 
	p = A;
	
	while( index < 300 )
	{
		q = p.binary_search(C, D);
		p = q.binary_search(A, B);
		p.print();
		q.print();
		index++;
	}
	cout << p.distance(q) << endl;
	
	return 0;
}

// 재귀함수 구현할때는 &쓰지말자!! 
