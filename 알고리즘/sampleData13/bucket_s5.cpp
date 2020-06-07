#include<iostream>
#include<vector>
#include<fstream>
#include<map>
#include<unordered_map>
#include<queue>
using namespace std;
using namespace __gnu_cxx;

ifstream  in("bucket.inp");
ofstream out("bucket.out");
int k, cache[4][7];
string s, t, r;
vector<int> en;

void init(void){

    in>>k;
    for(int i = 1; i<= 3; i++)
        for(int j = 1; j<= k; j++){
            in>>cache[i][j];
            if(i == 2){
                s+=to_string(cache[i][j]);
                en.push_back(cache[i][j]);
            }
            if(i == 3)  t+=to_string(cache[i][j]);
        }
}

int Solve(){

    unordered_map <string, int> m;
    queue<vector<int>> q;
    string n;

    m.insert(make_pair(s, 0));
    en.push_back(0);
    q.push(en);

    while(!q.empty()){
        int cnt = q.front()[k];
        for(int i = 0; i< k; i++){
            for(int j = 0; j< k; j++){
                if( i == j || q.front()[i] == 0)    continue;
                vector<int> v = q.front();
                if(cache[1][j+1] <= v[j] + v[i]){
                    v[i] = v[i] + v[j] - cache[1][j+1];
                    v[j] = cache[1][j+1];
                }
                else{
                    v[j] += v[i];
                    v[i] = 0;
                }
                for(int l = 0; l< k; l++)    r += to_string(v[l]);
                if(t == r)  return cnt+1;
                if(m.find(r) == m.end()){
                    m.insert( make_pair(r, cnt+1) );
                    v[k] += 1;
                    q.push(v);
                }
                r= "";
            }
        }q.pop();
    }
    return 0;
}

int main(void){

    init();
    out<<Solve();
    in.close(); out.close();
    return 0;
}