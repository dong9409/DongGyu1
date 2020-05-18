
#include <fstream>
#include <iostream>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <math.h>
#include <stack>
using namespace std;


ifstream in("detroit.inp");
ofstream out("detroit.out");
int N;
int det[9][9];
int det_R[9][9]={0};

int det_C[9][9]={0};
int cnt = 0;
int cnt33 = 0;
void DFS(int n);
int main() {


    in>> N;
int cnt4=0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            in >> det[i][j];
            if (det[i][j] != 0) {

                    if((det_R[i][det[i][j]-1] == 1) ||  (det_C[j][det[i][j]-1] == 1) ){
                       cnt4++;

                    }
                det_R[i][det[i][j]-1] = 1;
                det_C[j][det[i][j]-1] = 1;
            }

        }
    }




        if(cnt4==0){
                 DFS(0);
        }
        else{

            cnt=0;
        }


    cout<<endl;

    cout<<cnt<<endl;
    out<<cnt;
    cout<<cnt33;

    return 0;
}



void DFS(int n) {
    cnt33++;


  int y = n%N;
    int x = n/N;

    if (n==N*N) {



        cnt++;

    }


    if (det[x][y]!=0){
           DFS(n+1);

    }
   else  {
        for (int i=0; i<N; i++) {
            if (!det_R[x][i] && !det_C[y][i]) {
                det_R[x][i] = 1;
                det_C[y][i] = 1;
                det[x][y] = i+1;

                DFS(n+1);

                det_R[x][i] = 0;
                det_C[y][i] = 0;
                det[x][y] = 0;
            }
        }
    }



}