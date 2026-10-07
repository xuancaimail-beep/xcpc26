#include <bits/stdc++.h>
using namespace std; 

typedef complex<double> cd;
const double pi = acos(-1);
int tot; 
vector<int> r; 

void fft(vector<cd> &a,  int op){
    for (int i = 0; i < tot; i++)
        if (i < r[i]) swap(a[i], a[r[i]]);
    for (int m = 2; m <= tot; m <<= 1){
        cd wk1 = {cos(pi * 2 / m), sin(pi * 2 / m) * op};
        for (int i = 0; i < tot; i += m){
            cd wk = {1, 0};
            for (int j = 0; j < m / 2; j++){
                cd x = a[j + i], y = a[j + i + m / 2] * wk;
                a[j + i] = x + y;
                a[j + i + m / 2] = x - y;
                wk = wk * wk1;
            }
        }
    }
}

signed main()
{
    ios::sync_with_stdio(false); 
    cin.tie(nullptr); 
    int n; cin >> n; 
    int m; cin >> m; 
    n++;  m++; 
    int bit = 0; 
    while((1 << bit) < (n + m + 1)) bit++; 
    tot = 1 << bit;
    r.resize(tot);
    for (int i = 0; i < tot; i++) r[i] = r[i / 2] / 2 + ((i & 1) ? tot / 2 : 0);
    vector<cd> a(tot), b(tot); 
    for(int i = 0; i < n; i++) cin >> a[i];  
    for(int i = 0; i < m; i++) cin >> b[i]; 
    fft(a, 1);
    fft(b, 1);
    vector<cd> conv(tot); 
    for(int i = 0; i < tot; i++) conv[i] = (a[i] * b[i]);
    fft(conv, -1); 
    for(int i = 0; i < n + m - 1; i++){
        cout << (int) (conv[i].real() / tot + 0.5) << " "; 
    }
}