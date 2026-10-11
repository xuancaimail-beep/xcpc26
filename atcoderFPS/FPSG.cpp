// 完全背包trick , 加入大小为m的物体，不需要枚举加入的数量，只需要从小到大枚举背包容量，加入物体的复杂度为O(V)
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
    int N, M, L; cin >> N >> M >> L; 
    int ans = 0; 
    vector<int> a(N + 1); 
    a[0] = 1; 
    for(int m = 1; m <= L; m++){
        for(int j = 0; j <= N; j++){
            if(j - m >= 0) a[j] += a[j - m]; 
            a[j] %= mod; 
        }
    }
    cout << a[N] << "\n"; 
    for(int m = 2; m <= M - L + 1; m++){
        vector<int> _ (N + 1); 
        for(int j = 0; j <= N; j++){
            _[j] = a[j];     
        }
        for(int j = 0; j <= N; j++){
            if(j - (m - 1)>= 0) _[j] -= a[j - (m - 1)];     
            _[j] = (_[j] + mod) % mod; 
        }

        a = _; 
        for(int j = 0; j <= N; j++){
            if(j - (m + L - 1) >= 0) a[j] += a[j - (m + L - 1)]; 
            a[j] %= mod; 
        }
        
        cout << a[N] << "\n"; 
    }
}

signed main(){
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t = 1; 
    while(t--) solve(); 
    return 0;     
}