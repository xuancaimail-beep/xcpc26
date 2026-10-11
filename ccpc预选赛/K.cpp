#include <bits/stdc++.h>
using namespace std; 
#define int long long
const int mod = 998244353;
int qpow(int base, int pow){
    int res = 1;
    while(pow){
        if(pow & 1LL) res = res * base % mod; 
        pow >>= 1LL;
        base = base * base % mod; 
    }
    return res; 
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 
    int n, m, t; cin >> n >> m >> t;
    string s; cin >> s; 
    s = " " + s; 
    vector<vector<pair<int,int>>> edge(n + 1);
    for(int i = 1; i <= m; i++){
        int u, v, w; cin >> u >> v >> w; 
        edge[u].push_back({v, w}); 
    }
    vector<array<int, 3>> ans(n + 1, {-1, -1, -1});  // min, num, exp
    function<array<int, 3>(int)> dfs =  [&](int x)->array<int, 3>{
        if(x == t){
            return ans[x] = {0, 1, 0}; 
        }
        if(ans[x][0] != -1){
            return ans[x]; 
        }
        if(s[x] == '1'){
            int mini = 1e16;
            for(auto [X, w]: edge[x]){
                auto [dist, num, exp] = dfs(X);
                mini = min(mini, dist + w);
            }
            int cnt = 0; 
            int E = 0; 
            for(auto [X, w]: edge[x]){
                auto [dist, num, exp] = ans[X]; 
                if(dist + w == mini){
                    cnt += num;
                    cnt %= mod; 
                    E += (exp + w) * num % mod;
                    E %= mod;
                }
            }
            E *= qpow(cnt, mod - 2); 
            E %= mod; 
            return ans[x] = {mini, cnt, E}; 
        }else{
            int mini = 1e16;
            for(auto [X, w]: edge[x]){
                auto [dist, num, exp] = dfs(X);
                mini = min(mini, dist + w);
            }
            int cnt = 0; 
            int E = 0; 
            for(auto [X, w]: edge[x]){
                auto [dist, num, exp] = ans[X]; 
                if(dist + w == mini){
                    cnt += num;
                    cnt %= mod; 
                }
                E += (exp + w) % mod;
                E %= mod;  
            }
            E *= qpow((int)edge[x].size(), mod - 2); 
            E %= mod; 
            return ans[x] = {mini, cnt, E}; 
        }
    };
    for(int i = 1; i <= n; i++){
        ans[i] = dfs(i);
        cout << ans[i][2] << " ";
    }
    cout << "\n";
}