#include <bits/stdc++.h>
using namespace std; 
#define int long long 
long long mod = 998244353, G = 3, Gi;
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

vector<int> rev; 
int tot = (1 << 20);
int bit = 20; 
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



void solve(){
    Gi = qpow(3, mod - 2); 
    jie[0] = 1; inv[0] = qpow(1, mod - 2); 
    for(int i = 1; i <= 1e6; i++){
        jie[i] = jie[i - 1] * i % mod;
        inv[i] = qpow(jie[i], mod - 2); 
    }
    int n, k; cin >> n >> k;
    vector<int> a(n + 1); 
    for(int i = 1; i <= n; i++){
        cin >> a[i]; 
    }

    function<vector<int>(int, int)> f = [&](int l, int r) -> vector<int>{
        if(l == r) {
            return {1, a[l]};
        }

        int mid = (l + r) / 2; 
        vector<int> A = f(l, mid);
        vector<int> B = f(mid + 1, r);
        bit = 0; 
        while((1 << bit) < (r - l + 1 + 2)) bit++; 
        tot = 1 << bit;
        // cout << l << " " << r << " " << tot << "tot\n"; 
        vector<int> c(tot); 
        int linv = qpow(tot, mod - 2); 
        rev.resize(tot);
        for(int i = 0; i< tot;i++){
            rev[i] = (rev[i>>1] >>1 ) | ( (i & 1) << ( bit - 1) );
        }
        A.resize(tot);
        B.resize(tot); 
        // if(l == 1 && r == 3){
        //     cout << "A\n"; 
        //     for(auto x:A) cout << x << " "; 
        //     cout <<"\n";
        //     cout << "B\n"; 
        //     for(auto x:B) cout << x << " "; 
        //     cout <<"\n"; 
        // }
        NTT(A, 1);
        NTT(B, 1); 
        for(int i = 0; i < tot; i++) c[i] = A[i] * B[i] % mod; 
        NTT(c, -1);
        for(int i = 0; i < (r - l + 2); i++) c[i] = c[i] * linv % mod; 
        for(int i = (r - l + 2); i < tot; i++) c[i] = 0; 
        c.resize(r - l + 2); 
        // if(l == 1 && r == 3){
        //     cout << "C\n"; 
        //     for(auto x:c) cout << x << " "; 
        //     cout <<"\n";
        // }
        return c; 
    }; 
    vector<int> res = f(1, n); 
    if(k <= n) cout << res[k] << "\n"; 
    else cout << 0 << "\n"; 
}

signed main(){
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t = 1; 
    while(t--) solve(); 
    return 0;     
}