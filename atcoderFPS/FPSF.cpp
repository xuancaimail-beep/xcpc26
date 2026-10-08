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
    int N; cin >> N; 
    int ans = qpow(3, N); 
    if(N % 2 == 0) ans--; 
    else ans++; 
    ans %= mod; 
    cout << ans * qpow(4, mod - 2) % mod << "\n"; 
}

signed main(){
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t = 1; 
    while(t--) solve(); 
    return 0;     
}