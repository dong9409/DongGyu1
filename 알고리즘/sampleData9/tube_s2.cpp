#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int sum_vector_values(vector <int> &v){
    int sum=0;
    for(auto& e : v){
        sum += e;
    }
    return sum;
}

void print_vector(vector <int> &v){
    for(auto& e : v){
            cout << e <<endl;
    }
}

int main()
{
    // data input
    int l,k,ans;
    //ifstream in("샘플데이터/sampleData9/3.inp");
    ifstream in("tube.inp");
    in >> l;
    in >> k;
    vector <int> tubes(k+1);  // 사용가능한 tube의 종류들을 저장 
    vector <int> min_used(l+1); //  최소사용횟수를 저장                0 1 2 3 4 5 6 7 8 9 10 ... 26 27 28 29   -> k=30
    for(int i=1; i<=k; i++){
        in >> tubes[i];        // 1 2 3
    }                          // 5 6 10 

    for(int i=1; i<=k; i++){ // k종류의 tubes
        int tmp_tube = tubes[i];                   // 5 6 10 3가지 종류의 튜브라고 할 때 
        for(int j = tmp_tube; j<l+1; j++){         //tmp~k까지    0  1 2 3 4 5 6 7 8 9 10 ... 26 27 28 29 30
                                                              // 0  0 0 0 0 1 0 0 0 0 2 ..... tube를 5로만 나타낼 경우,
                                                              // 0  0 0 0 0 0 0 0 0 0 1 ..... tube를 10로만 나타낼 경우,
            if(j==tmp_tube){
                min_used[j] = 1; // 값 j를 만드는 최소횟수
            }else{
                if(min_used[j-tmp_tube]!=0){ // 그 전에 만들수 있는 값이 0이 아니고
                    if( min_used[j]==0 || min_used[j] > min_used[j-tmp_tube] ){ // 지금게 0이거나, 전에것 보다 크다면
                        min_used[j] = min_used[j-tmp_tube] + 1; // 전에 것보다 하나 더한 값을 넣는다.
                    }
                }                   
            }
        }
        //cout<< i <<"------"<< endl;
        //print_vector(min_used); 
    }

    if(min_used[l]==0){
        ans=0;
    }else{
        ans=min_used[l];
    }

    // cout << ans;

    // output
    ofstream out("tube.out");
    out << ans;
    return 0;
}