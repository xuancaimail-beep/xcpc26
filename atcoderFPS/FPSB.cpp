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
    int D, N; cin >> D >> N; 
    int ans = 0; 
    if(N - D < 0) {
        cout << 0 << "\n"; 
        return; 
    }
    for(int i = 0; 2 * i <= N - D ; i++){
        int num2 = N - D - 2 * i;
        if(num2 % 3 == 0){
            if(D - i < 0) continue;
            int fac1 = jie[D] * inv[i] % mod * inv[D - i] % mod;   
            int p = num2 / 3; 
            if(D - p < 0) continue; 
            int fac2 =  jie[D] * inv[p] % mod * inv[D - p] % mod;
            ans = (ans + fac1 * fac2 % mod) % mod; 
        }
    }
    cout << ans << "\n"; 
}

signed main(){
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    // int t = 1; 
    // while(t--) solve(); 
    int x; cin >> x; 
    cout << (x + 1 ) % 998244353<< "\n"; 
    return 0;     
}