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
    int res = 0; 
    int N, M, S; cin >> N >> M >> S;
    for(int i = 0; i <= N; i++){
        if(i *(M + 1) > S) break; 
        int xi = jie[N] * inv[i] % mod * inv[N - i] % mod; 
        if(i % 2 == 1) xi *= -1; 
        xi = (xi + mod) % mod;  
        // cout << i << " " << xi << " "; 
        int j = S - i * (M + 1); 
        xi *= jie[N + j - 1] * inv[N -1] % mod * inv[j] % mod;
        xi %= mod;
        // cout << xi << "\n"; 
        res += xi; 
        res %= mod; 
    }
    cout << res << "\n"; 
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t = 1; 
    while(t--) solve(); 
    return 0;     
}