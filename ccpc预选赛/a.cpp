#include <bits/stdc++.h>
using namespace std;

void solve(){



    int n; cin >> n; 
    // map<int, int> a_b;
    // map<int, int> a_c;
    // map<int, int> b_c;
    vector<int> a_b(n + 1); 
    vector<int> b_c(n + 1); 
    vector<int> a_c(n + 1); 
    int numa_b = 0;
    int numa_c = 0; 
    int numb_c = 0; 
    vector<int> a(n + 1), b(n + 1), c(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i]; 
    for(int i = 1; i <= n; i++) cin >> b[i]; 
    for(int i = 1; i <= n; i++) cin >> c[i]; 
    int res = 0; 
    for(int i = 1; i <= n; i++){
        a_b[a[i]]++; 
        if(a_b[a[i]] == 0 ) numa_b++; 
        a_b[b[i]]--; 
        if(a_b[b[i]] == 0) numa_b++; 
        a_c[a[i]]++; 
        if(a_c[a[i]] == 0) numa_c++; 
        a_c[c[i]]--; 
        if(a_c[c[i]] == 0) numa_c++; 
        b_c[b[i]]++; 
        if(b_c[b[i]] == 0) numb_c++; 
        b_c[c[i]]--; 
        if(b_c[c[i]] == 0) numb_c++; 
        if(numa_b == i || numa_c == i || numb_c == i) res++;  
        // cout << i << res << "\n"; 
    }
    cout << res << "\n"; 
}



signed main(){
    ios::sync_with_stdio(false); cin.tie(nullptr); 
    int t; cin >> t;
    while(t--) solve(); 
    return 0; 
}