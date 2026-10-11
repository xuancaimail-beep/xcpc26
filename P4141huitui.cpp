#include <bits/stdc++.h>
using namespace std; 
#define int long long

signed main(){
    int n, v; cin >> n >> v; 
    vector<int> w(n + 1); 
    for(int i = 1; i <= n; i++) cin >> w[i]; 
    vector<int> dp(v + 1); 
    dp[0] = 1; 
    for(int i = 1;i <= n; i++){
        for(int j = v; j >= 0; j--){
            if(j - w[i] >= 0) dp[j] = (dp[j] + dp[j - w[i]]) % 10; 
        }
    }
    for(int i = 1;i <= n; i++){
        vector<int> _ = dp; 
        for(int j = w[i]; j <= v; j++){
            _[j] -= _[j - w[i]];
            _[j] = (_[j] + 10) % 10; 
        }
        for(int j = 1; j <= v; j++){
            cout << _[j] % 10; 
        }
        cout << "\n"; 
    }
}