#include <bits/stdc++.h>
using namespace std;
#define int long long 
const int mod = 998244353; 
const int G = 3; 
const int g = 332748118;
const int N = 1025;
int l; int tot; 
vector<int> jie(N), inv(N);
vector<int> rev; 
int qpow(int base, int pow){
    int res = 1; 
    while(pow){
        if(pow & 1LL) res = res * base % mod; 
        pow >>= 1LL;
        base = base * base % mod; 
    }
    return res; 
}

void NTT(vector<int> &c, int inv)
{
    for (int i = 0; i < tot; i++){
        if (i < rev[i]) swap(c[i], c[rev[i]]);
    }
    for (int mid = 1; mid < tot; mid <<= 1){  // 枚举每个子问题的mid
        int w1 = qpow(G, (mod - 1) / (mid << 1)); // g^{(mod-1)/N}
        if(!(~inv))
            w1 = qpow(w1, mod - 2); // 如果是逆变换,要在指数上变负号
        for(int i = 0, len = mid << 1; i < tot; i += len){
            int wk = 1;
            for (int j = 0; j < mid; j++, wk = (wk * w1) % mod){ // 处理一半足矣
                int x = c[i + j], y = wk * c[i + j + mid] % mod;
                c[i + j] = (x + y) % mod;
                c[i + j + mid] = (x - y + mod) % mod;
            }
        }
    }
}

signed main(){
    jie[0] = 1; inv[0] = qpow(1, mod - 2); 
    for(int i = 1; i <= 1024; i++){
        jie[i] = jie[i - 1] * i % mod;
        inv[i] = qpow(jie[i], mod - 2); 
    }
    int n, m; cin >> n >> m;
    l = (1 << 10); //512
    tot = l; 
    int bit = 10; 
    int linv = qpow(l, mod - 2); 
    vector<int> a(l);
    rev.resize(l); 
    for(int i= 0; i < l; i++) rev[i] = ( rev[i>>1] >>1 ) | ( (i & 1) << ( bit - 1) );
    a[0] = 1;
    a[1] = 1;
    for(int i = 2; i <= m; i++) {
        vector<int> cur(l);
        for(int j = 0; j <= i; j++){
            cur[j] = inv[j];
        }
        NTT(cur, 1);
        NTT(a, 1);
        vector<int> c(l); 
        for(int j = 0; j < l; j++){
            c[j] = a[j] * cur[j]  % mod ;    
        }
        NTT(c, -1); 
        for(int j = 0; j <= n; j++){
            c[j] = c[j] * linv % mod; 
        }
        for(int j = n + 1; j < l; j++){
            c[j] = 0; 
        }
        a = c; 
    }
    cout << a[n] * jie[n]  % mod; 
}