#include <bits/stdc++.h>
using namespace std;
using T = long long;
using ll = long long;
const long long mod = 1004535809, G = 3, Gi = 334845270;
int tot;
vector<int> rev;
T fastpow(T a, T b){
    T res = 1;
    while (b){
        if (b & 1) res = (res * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }
    return res;
}

T Inv(T x){
    return fastpow(x, mod - 2);
}

void NTT(vector<int> &c, int inv)
{
    for (int i = 0; i < tot; i++){
        if (i < rev[i]) swap(c[i], c[rev[i]]);
    }
    for (int mid = 1; mid < tot; mid <<= 1){  // 枚举每个子问题的mid
        int w1 = fastpow(G, (mod - 1) / (mid << 1)); // g^{(mod-1)/N}
        if(!(~inv))
            w1 = fastpow(w1, mod - 2); // 如果是逆变换,要在指数上变负号
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

signed main()
{
    int n; cin >> n; 
    int m; cin >> m; 

    int bit = 0; 
    while((1 << bit) < (n + m + 1)) bit++; 
    tot = 1 << bit;
    rev.resize(tot);
    vector<T> a(tot), b(tot); 
    for(int i = 0; i < n; i++){
        ll x; cin >> x;
        a[i] = x; 
    }
    for(int i = 0; i < m; i++) {
        ll x; cin >> x; 
        b[i] = x;  
    }
    for(int i = 0; i< tot;i++){
		rev[i] = (rev[i>>1] >>1 ) | ( (i & 1) << ( bit - 1) );
	}
    NTT(a, 1);
    NTT(b, 1);
    T _tot = Inv(tot); 
    vector<T> conv(tot); 
    for(int i = 0; i < tot; i++){
        conv[i] = (a[i] * b[i])  % mod; 
    }
    NTT(conv, -1); 

    for(int i = 0; i < n + m - 2 + 1; i++){
        cout << (ll) (conv[i] * _tot % mod) << " "; 
    }
}

