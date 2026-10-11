#include <bits/stdc++.h>
using namespace std;
int dp[41][41][1000];  //jie, sumn, sumk
int _[41]; 
signed main(){
    int n, b, k; cin >> n >> b >> k; 
    dp[0][0][0] = 1;
    int sum = 0;
    for(int j = 1; j <= 40; j++){
        sum += (j - 1); 
        _[j] = sum;
    }
    for(int i = 1; i <= b; i++){
        for(int j = 0; j <= n; j++){
            for(int kk = 0; kk <= k; kk++){
                for(int nw = 1; nw <= n; nw++){
                    if(j + nw <= n && kk + _[nw] <= k) dp[i][j + nw][kk + _[nw]] +=  dp[i - 1][j][kk];                
                }
            }
        }
    }
    // cout << dp[0][0][0] << "  " << dp[1][2]0[3] << " " << dp[2][3][4] << "\n";
    if(dp[b][n][k] == 0){
        cout << "IMPOSSIBLE\n"; 
    }else{
        vector<int> r;
        int curl = n; 
        int curw = k; 
        for(int i = b; i >= 1; i--){
            int fl = 0; 
            int ok = 0;
            for(int nw = 1; nw <= n; nw++){
                if(dp[i - 1][curl - nw][curw - _[nw]] > 0){
                    curl -= nw; 
                    curw -= _[nw]; 
                    r.push_back(nw);
                    break;  
                }
            }
        }
        // cout << r.size() << "\n"; 
        for(int i = (int)r.size() - 1; i >= 0; i--){
            cout << r[i] << " "; 
        }
        cout << "\n"; 
        int num = 0; 
        for(int i = (int)r.size() - 1; i >= 0; i--){
            int nummax = num +(int) r[i]; 
            for(int j = nummax; j >= num + 1; j--){
                cout << j << " "; 
            }
            num += r[i]; 
        }
        cout << "\n";

    }
    
}