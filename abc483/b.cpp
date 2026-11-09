#include <bits/stdc++.h> 
using namespace std;

void solve(){
    int n, q; cin >> n >> q;
    vector<int> a(n + 1),b(n + 1); 
    for(int i = 1; i <= n; i++) a[i] = i;
    while(q--){
        int num; cin >> num; 
        b = a; 
        for(int i = 1; i <= num; i++){
            b[num + 1 - i] = -a[i];    
        }
        a = b;
    }
    for(int i = 1; i <= n; i++){
        cout << a[i] << "\n"; 
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 
    int t = 1;
    // cin >> t;
    while(t--) solve(); 
}