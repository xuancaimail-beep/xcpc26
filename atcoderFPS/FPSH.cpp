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

vector<int> jie(1e6 + 10); 
vector<int> inv(1e6 + 10); 
void solve(){
    jie[0] = 1; inv[0] = qpow(1, mod - 2); 
    for(int i = 1; i <= 1e6; i++){
        jie[i] = jie[i - 1] * i % mod;
        inv[i] = qpow(jie[i], mod - 2); 
    }
    int N, M; cin >> N >> M;
    int res = 0;
    for(int k = 0; k <= M; k++){
        res += jie[N + M - 1] * inv [N + k - 1] % mod * inv[M - k] % mod  * jie[N + k] % mod * inv[N] % mod * inv[k] % mod;
        res %= mod;  
    }
    cout << res << "\n";
}

signed main(){
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t = 1; 
    while(t--) solve(); 
    return 0;     
}