#include<bits/stdc++.h>
using namespace std;
#define MAX 200000000

int dp[100001];

int main() {
    int N, len, tube[11];

    ifstream in("3.inp");
    in >> len >> N;
    for (int i = 0; i < N; i++){
        in >> tube[i];
    }

    // INT_MAX로 초기화
    dp[0] = 0;
    for (int i = 1; i <= len; i++){
        dp[i] = MAX;
    }


    for (int i = 0; i < N; i++){
        for (int j = tube[i]; j <= len; ++j){
            dp[j] = min(dp[j], dp[j - tube[i]]+1);
        }
    }

    if(dp[len]==MAX) cout << 0 << endl;
    cout << dp[len];
    return 0;

}
