#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
using namespace std;

ifstream  in("drone.inp");
ofstream out("drone.out");
const static int INF = 987654321;
int n, cache[21][4], dist[21], w = 1, value = INF, visited = 1;
pair<int, int> near[21][21];

int calc(int i, int j){
    return abs(cache[i][2]-cache[j][2]) + abs(cache[i][3]-cache[j][3]);
}

void init(void){

    in>>n;
    int idx;
    for(int i = 1; i<= n; i++){
        in>>idx;
        in>>cache[idx][1]>>cache[idx][2]>>cache[idx][3];
        w += cache[idx][1];
    }

    for(int i = 1; i<= n; i++){
        for(int j = i+1; j<= n; j++){
            int d = calc(i, j);
            if(i == 1) dist[j] = d;
            near[i][j].first = near[j][i].first = d;
            near[i][j].second = j;
            near[j][i].second = i;
        }
        sort(near[i], near[i]+ n+1);
    }
}

int Solve(int position, int weight, int cost){

    if(cost > value) return INF;
    if(visited == ((1<<n)-1)){
        value = min(value, cost + dist[position]);
        return cost + dist[position];
    }

    int ret = INF;
    for(int i = 2; i<= n; i++){
        int k = near[position][i].second;
        if(!(visited & 1<<(k-1) )){
            visited |= 1<<(k-1);
            ret = min(ret, Solve(k, weight - cache[k][1], cost + weight * near[position][i].first ));
            visited &= ~(1<<(k-1));
        }
    }
    return ret;
}

int main(void){

    init();
    out<<Solve(1, w, 0);
    in.close(); out.close();
    return 0;
}