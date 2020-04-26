#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

struct Point {
	double x, y, z;
};

double dist(Point& a, Point& b) {
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}

int mdist(Point& a, Point& b, Point& p) {
	Point s;
	s.x = (a.x + b.x) / 2;
	s.y = (a.y + b.y) / 2;
	s.z = (a.z + b.z) / 2;
	
	int dap, dbp;
	dap = ceil(dist(a, p));
	dbp = ceil(dist(b, p));
	
	if (dap == dbp) {
		int dsp = ceil(dist(s, p));
		return dsp;
	}
	else if (dap > dbp)
		return mdist(s, b, p);
	else
		return mdist(a, s, p);
}

int main() {
	ifstream in("station.inp");
    
    Point a, b, p;
    in >> a.x >> a.y >> a.z;
    in >> b.x >> b.y >> b.z;
    in >> p.x >> p.y >> p.z;
	
    ofstream out("station.out");
    out << mdist(a, b, p);
}