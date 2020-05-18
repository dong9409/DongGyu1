#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

bool done = false;
int cnt=0;
//int check_rec_time=0;

void print_table(vector <vector <int>>& v){
    int size = v[0].size();
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            cout << v[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

bool check_table(vector <vector <int>>& v, int p, int q, int value, int size){
    //int size = v[0].size();
    // 열 비교해서 같은 숫자있으면 false return.
    for(int i=0; i<size; i++){
        if(v[i][q]==value && i!=p){
            return false;
        }
    }
    // 행 마찬가지 비교
    for(int j=0; j<size; j++){
        if(v[p][j]==value && j!=q){
            return false;
        }
    }
    return true;
}

// int detroit(vector <vector <int>>& v, int size){
//     // int size = v[0].size();

//     for(int i=0; i<size; i++){
//         for(int j=0; j<size; j++){
//             if(v[i][j]==0){ // 값이 채워지지 않은 경우
//                 for(int num=1; num<=size; num++){// 안에 넣을 수 있는 숫자는 1~N까지
//                     if(check_table(v,i,j,num,size)){ // 검사 통과하면
//                         v[i][j] = num; // 값 넣고 
//                         //print_table(v);
//                         detroit(v,size); // 추가된 테이블로 계속 채운다.
//                         // 끝나면 종료 -> 리커전 했던 모든 경우를 종료.
//                         v[i][j] = 0; // 만약 그 경로로 끝내지 못하면 0으로 돌리고 다음숫자로 시도
//                     } 
//                 }
//                 return 0; // 만약에 i,j의 경우에 num 1~9까지 전부 시도했는데 다음테이블로 못넘어 가면 잘못된것.
//             }
//         }
//     }
//     // done = true; // 전부 다 채운 경우
//     // print_table(v);
//     cnt++;
//     return 0;
// }

int detroit(vector <vector <int>>& v, int size,int start){
    // int size = v[0].size();
    int row=0;
    int i;
    while(row<size){
        i=start;
        for(int j=0; j<size; j++){
            if(v[i][j]==0){ // 값이 채워지지 않은 경우
                for(int num=1; num<=size; num++){// 안에 넣을 수 있는 숫자는 1~N까지
                    if(check_table(v,i,j,num,size)){ // 검사 통과하면
                        v[i][j] = num; // 값 넣고 
                        //print_table(v);
                        detroit(v,size,start); // 추가된 테이블로 계속 채운다.
                        v[i][j] = 0; // 만약 그 경로로 끝내지 못하면 0으로 돌리고 다음숫자로 시도
                    } 
                }
                return 0; // 만약에 i,j의 경우에 num 1~9까지 전부 시도했는데 다음테이블로 못넘어 가면 잘못된것.
            }
        }
        start++;
        if(start==size) start=0;
        row++;
    }

    // done = true; // 전부 다 채운 경우
    // print_table(v);
    cnt++;
    return 0;
}

int main()
{
    // data input
    bool notzero=true;
    int N,most_num_row=0,num_count=0,prev=0;
    //ifstream in("샘플데이터/sampleData10/4.inp");
    ifstream in("detroit.inp");
    in >> N;
    vector < vector <int>> table(N , vector<int> (N,0));
    for(int i=0; i<N; i++){
        num_count=0;
        for(int j=0; j<N; j++){
            in >> table[i][j];
            if(table[i][j]!=0){
                num_count++;
            }
        }
        if(prev<num_count){
            prev = num_count;
            most_num_row=i;
        }
    }

    //print_table(table);

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            int k = table[i][j];
            if(k!=0){
                //cout << check_table(table,i,j,k,N) << " ";
                if(!check_table(table,i,j,k,N)){
                    notzero=false;
                }
            }
            //cout << notzero << " ";
        }
    }
    // cout << most_num_row;

    // DFS
    if(notzero){
        //cout << "wow" << endl;
        detroit(table,N,most_num_row);
    }

    // output
    ofstream out("detroit.out");
    //cout << cnt;
    out << cnt;
    return 0;
}