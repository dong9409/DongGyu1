#include <fstream>
#include <cmath>
#include <queue>
#define MAXI 2147483647
using namespace std;

int drone[21][3], l[21][21], arr[21], sq[20], N, weight, mov, e, min_e = MAXI;
priority_queue <int> s;
inline void get_data()
{
	ifstream in("drone.inp");
	in >> N;
	for (int i = 0; i < N; i++) {
		int temp;
		in >> temp;
		in >> drone[temp][0] >> drone[temp][1] >> drone[temp][2];
		s.push(drone[temp][0] * 100 + temp);
		weight += drone[temp][0];
	}
	for (int i = 0; !s.empty(); i++) {
		sq[i] = s.top() % 100;
		s.pop();
	}
	in.close();
	weight++;
}

inline void how_far()
{
	for (int i = 1; i <= N; i++) {
		for (int j = i + 1; j <= N; j++) {
			l[i][j] = abs(drone[i][1] - drone[j][1]) + abs(drone[i][2] - drone[j][2]);
		}
	}

	for (int i = 1; i <= N; i++) {
		for (int j = i + 1; j <= N; j++) {
			l[j][i] = l[i][j];
		}
	}
}

void seek(int here)
{
	if (mov == N - 1) {
		e += l[1][here];
		if (e < min_e) { min_e = e; }
		e -= l[1][here];
		return;
	}
	for (int i = 0; i < N; i++) {
		if (!arr[sq[i]] && sq[i] != here) {
			e += weight * l[sq[i]][here];
			if (e + l[sq[i]][1] < min_e) {
				weight -= drone[sq[i]][0];
				arr[sq[i]] = 1;
				mov++;
				seek(sq[i]);
				weight += drone[sq[i]][0];
				arr[sq[i]] = 0;
				mov--;
			}
			e -= weight * l[sq[i]][here];
		}
	}
}

main()
{
	get_data();
	how_far();
	arr[1] = 1;
	seek(1);
	ofstream out("drone.out");
	out << min_e;
	out.close();
}