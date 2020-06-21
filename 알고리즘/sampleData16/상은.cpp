#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct{
    pair<int,int> mypair;
    int area;
    int num;
}mystruct;
int n;
//y==0 -> x>0 y>0,
//0 a.x b.x 0
//0 a.y b.y 0
//0*a.y + a.x*b.y + b.x*0 -(0*a.x + b.x*a.y + 0*b.y)
int signed_area(mystruct a,mystruct b){
    return (((0*a.mypair.second)+(a.mypair.first*b.mypair.second)+(b.mypair.first*0)) - ((0*a.mypair.first)+(b.mypair.first*a.mypair.second)+(0*b.mypair.second)));
}
bool myfun(mystruct a,mystruct b){
    int areaA, areaB;
    areaA = signed_area(a, b);
    areaB = signed_area(b, a);
    if(areaB==areaA){
        if(a.mypair.first==0) return a.mypair.second>b.mypair.second;
        else if(a.mypair.second==0) return a.mypair.first>b.mypair.first;
        else return a.mypair.first*a.mypair.second > b.mypair.first*b.mypair.second;
    }
    return (areaA > areaB);
}
int main() {
    ifstream in("1.inp");
//    ofstream out("angle.out");
    in >> n;
    mystruct s;
    vector<mystruct> point1, point2, point3, point4;
    
    for(int i=0;i<n;i++){
        int n1,n2;
        in >> n1 >> n2;
        s.mypair = make_pair(n1,n2);
        s.num = i+1;
        if(n1>=0 && n2>=0)
            point1.push_back(s);
        else if(n1<0 && n2>=0)
            point2.push_back(s);
        else if(n1<0 && n2<0)
            point3.push_back(s);
        else if(n1>=0 && n2<0)
            point4.push_back(s);
    }

    sort(point1.begin(),point1.end(),myfun);
    sort(point2.begin(),point2.end(),myfun);
    sort(point3.begin(),point3.end(),myfun);
    sort(point4.begin(),point4.end(),myfun);
    for(auto p : point1)
            cout << p.num <<'\n';
    for(auto p : point2)
           cout << p.num <<'\n';
    for(auto p : point3)
           cout << p.num <<'\n';
    for(auto p : point4)
           cout << p.num <<'\n';
  //  out.close();
    return 0;
}
