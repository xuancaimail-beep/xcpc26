#include <bits/stdc++.h> 
using namespace std;
#define int long long
void solve(){
    int n, m;  cin >> n >> m;
    vector<string> s(n + 1); 
    for(int i = 1;i <= n; i++){
        cin >> s[i]; 
    }
    int ans = 0; 
    unordered_map<string, int> snum; 
    for(int i = 1; i <= n; i++){
        // ans += snum[s[i]];
        int xi = m * (1 -(m - 1)) + m * (m - 1)/2;  
        ans -= snum[s[i]] * xi;
        ans += snum[s[i]]; 
        for(int j = 0; j < m; j++){
            string s2 = s[i]; 
            s2[j] = '*'; 
            ans += snum[s2]; 
            ans -= snum[s2] * (m -1); 
            // ans -= snum[s2] * (m - 1 - (j + 1)  + 1); 
            for(int k = j + 1; k < m; k++){
                // s1 = s[i]; 
                // s1[j] = '*';
                char x = s2[k]; 
                s2[k] = '*';      
                ans += snum[s2];
                s2[k] = x;   
            }
        }
        
        snum[s[i]]++; 
        for(int j = 0; j < m; j++){
            string s2 = s[i]; 
            s2[j] = '*'; 
            snum[s2]++; 
            for(int k = j + 1; k < m; k++){
                // string s1 = s[i]; 
                // s1[j] = '*';
                char x = s2[k]; 
                s2[k] = '*'; 
                snum[s2]++;
                s2[k] = x;  
            }
        }
        // cout << ans << "\n";  
    }

    cout << ans << "\n"; 
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 
    int t = 1;
    // cin >> t;
    while(t--) solve(); 
}